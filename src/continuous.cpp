/* -*- c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* ====================================================================
 * Copyright (c) 1999-2010 Carnegie Mellon University.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced 
 * Research Projects Agency and the National Science Foundation of the 
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
/*
 * continuous.c - Simple pocketsphinx command-line application to test
 *                both continuous listening/silence filtering from microphone
 *                and continuous file transcription.
 */

/*
 * This is a simple example of pocketsphinx application that uses continuous listening
 * with silence filtering to automatically segment a continuous stream of audio input
 * into utterances that are then decoded.
 * 
 * Remarks:
 *   - Each utterance is ended when a silence segment of at least 1 sec is recognized.
 *   - Single-threaded implementation for portability.
 *   - Uses audio library; can be replaced with an equivalent custom library.
 */

#include <stdio.h>
#include <string.h>

#if !defined(_WIN32_WCE)
#include <signal.h>
#include <setjmp.h>
#endif
#if defined(WIN32) && !defined(GNUWINCE)
#include <time.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

#include "aibot.h"
#include "continuous.h"

static ps_decoder_t *ps;
static cmd_ln_t *config;
static FILE* rawfd;

static int32
ad_file_read(ad_rec_t * ad, int16 * buf, int32 max)
{
	size_t nread;

	nread = fread(buf, sizeof(int16), max, rawfd);

	return (nread > 0 ? nread : -1);
}

static void
print_word_times(int32 start)
{
	ps_seg_t *iter = ps_seg_iter(ps, NULL);
	while (iter != NULL) {
		int32 sf, ef, pprob;
		float conf;

		ps_seg_frames(iter, &sf, &ef);
		pprob = ps_seg_prob(iter, NULL, NULL, NULL);
		conf = logmath_exp(ps_get_logmath(ps), pprob);
		printf("%s %f %f %f\n", ps_seg_word(iter), (sf + start) / 100.0, (ef + start) / 100.0, conf);
		iter = ps_seg_next(iter);
	}
}

/*
* Continuous recognition from a file
*/
static void
recognize_from_file() {
	cont_ad_t *cont;
	ad_rec_t file_ad = { 0 };
	int16 adbuf[4096];
	const char* hyp;
	const char* uttid;
	int32 k, ts, start;

	char waveheader[44];
	if ((rawfd = fopen(cmd_ln_str_r(config, "-infile"), "rb")) == NULL) {
		E_FATAL_SYSTEM("Failed to open file '%s' for reading",
			cmd_ln_str_r(config, "-infile"));
	}

	fread(waveheader, 1, 44, rawfd);

	file_ad.sps = (int32)cmd_ln_float32_r(config, "-samprate");
	file_ad.bps = sizeof(int16);

	if ((cont = cont_ad_init(&file_ad, ad_file_read)) == NULL) {
		E_FATAL("Failed to initialize voice activity detection");
	}
	if (cont_ad_calib(cont) < 0)
		E_FATAL("Failed to calibrate voice activity detection\n");
	rewind(rawfd);

	for (;;) {

		while ((k = cont_ad_read(cont, adbuf, 4096)) == 0);

		if (k < 0) {
			break;
		}

		if (ps_start_utt(ps, NULL) < 0)
			E_FATAL("ps_start_utt() failed\n");

		ps_process_raw(ps, adbuf, k, FALSE, FALSE);

		ts = cont->read_ts;
		start = ((ts - k) * 100.0) / file_ad.sps;

		for (;;) {
			if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
				break;

			if (k == 0) {
				/*
				* No speech data available; check current timestamp with most recent
				* speech to see if more than 1 sec elapsed.  If so, end of utterance.
				*/
				if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
					break;
			}
			else {
				/* New speech data received; note current timestamp */
				ts = cont->read_ts;
			}


			ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		}

		ps_end_utt(ps);

		if (cmd_ln_boolean_r(config, "-time")) {
			print_word_times(start);
		}
		else {
			hyp = ps_get_hyp(ps, NULL, &uttid);
			printf("%s: %s\n", uttid, hyp);
		}
		fflush(stdout);
	}

	cont_ad_close(cont);
	fclose(rawfd);
}

/* Sleep for specified msec */
static void
sleep_msec(int32 ms)
{
#if (defined(WIN32) && !defined(GNUWINCE)) || defined(_WIN32_WCE)
	Sleep(ms);
#else
	/* ------------------- Unix ------------------ */
	struct timeval tmo;

	tmo.tv_sec = 0;
	tmo.tv_usec = ms * 1000;

	select(0, NULL, NULL, NULL, &tmo);
#endif
}


static void microphoneInit(mic_data_t &md)
{
	if ((md.ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
		(int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
		E_FATAL("Failed to open audio device\n");

	/* Initialize continuous listening module */
	if ((md.cont = cont_ad_init(md.ad, ad_read)) == NULL)
		E_FATAL("Failed to initialize voice activity detection\n");
	if (ad_start_rec(md.ad) < 0)
		E_FATAL("Failed to start recording\n");
	if (cont_ad_calib(md.cont) < 0)
		E_FATAL("Failed to calibrate voice activity detection\n");

	//Stop recording and flush data and wait till getUtterance is called
	ad_stop_rec(md.ad);
	while (ad_read(md.ad, md.adbuf, 4096) >= 0);
	cont_ad_reset(md.cont);
}

/*
* Wait for start of next utterance
*/
void getUtterance(mic_data_t &md)
{	
	int32 k, ts, tsfirst, rem;
	int32 maxListenTime = 50000; //50000 = 5 secs

	/* Resume A/D recording for next utterance */
	if (ad_start_rec(md.ad) < 0)
		E_FATAL("Failed to start recording\n");

	/* Indicate listening for next utterance */
	printf("READY....\n");
	fflush(stdout);
	fflush(stderr);

	/* Wait data for next utterance */
	while ((k = cont_ad_read(md.cont, md.adbuf, 4096)) == 0)
		sleep_msec(100);

	if (k < 0)
		E_FATAL("Failed to read audio\n");

	/*
	* Non-zero amount of data received; start recognition of new utterance.
	* NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
	*/
	if (ps_start_utt(ps, NULL) < 0)
		E_FATAL("Failed to start utterance\n");
	ps_process_raw(ps, md.adbuf, k, FALSE, FALSE);
	printf("Listening...\n");
	fflush(stdout);

	/* Note timestamp for this first block of data */
	ts = md.cont->read_ts;

	/* Added by hadi */
	tsfirst = ts;

	/* Decode utterance until end (marked by a "long" silence, >1sec) */
	for (;;) {
		/* Read non-silence audio data, if any, from continuous listening module */
		if ((k = cont_ad_read(md.cont, md.adbuf, 4096)) < 0)
			E_FATAL("Failed to read audio\n");
		if (k == 0) {
			/*
			* No speech data available; check current timestamp with most recent
			* speech to see if more than 1 sec elapsed.  If so, end of utterance.
			*/
			if ((md.cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
				break;
		}
		else {
			/* New speech data received; note current timestamp */
			ts = md.cont->read_ts;

			/* Added by hadi */
			if ((ts - tsfirst) > maxListenTime)
			{
				break;
			}
		}

		/*
		* Decode whatever data was read above.
		*/
		rem = ps_process_raw(ps, md.adbuf, k, FALSE, FALSE);

		/* If no work to be done, sleep a bit */
		if ((rem == 0) && (k == 0))
			sleep_msec(20);
	}

	/*
	* Utterance ended; flush any accumulated, unprocessed A/D data and stop
	* listening until current utterance completely decoded
	*/
	ad_stop_rec(md.ad);
	while (ad_read(md.ad, md.adbuf, 4096) >= 0);
	cont_ad_reset(md.cont);

	printf("Stopped listening, please wait...\n");
	fflush(stdout);
	/* Finish decoding, obtain and print result */
	ps_end_utt(ps);
	md.hyp = ps_get_hyp(ps, NULL, &md.uttid);
	printf("%s: %s\n", md.uttid, md.hyp); //hyp is the recognized text
	fflush(stdout);
	md.prob = logmath_exp(ps_get_logmath(ps), ps_get_prob(ps, &md.uttid));
	printf("Probability Float: %f\n", md.prob);
}

/*
* Main utterance processing loop:
*     for (;;) {
* 	   wait for start of next utterance;
* 	   decode utterance until silence of at least 1 sec observed;
* 	   print utterance result;
*     }
*/
static void
recognize_from_microphone()
{
	char word[256];
	mic_data_t md;

	microphoneInit(md);

	for (;;) {
		getUtterance(md);

		/* Exit if the first word spoken was GOODBYE */
		if (md.hyp) {
			sscanf(md.hyp, "%s", word);
			if (strcmp(word, "goodbye") == 0)
				break;
		}
	}

	cont_ad_close(md.cont);
	ad_close(md.ad);
}

static jmp_buf jbuf;
static void
sighandler(int signo)
{
	longjmp(jbuf, 1);
}

void
continuous_init(Arguments& arguments, mic_data_t &md)
{
	E_INFO("%s COMPILED ON: %s, AT: %s\n\n", arguments.getExeName().c_str(), __DATE__, __TIME__);

	printf("config\n");
	config = arguments.ps_config;
	printf("ps_init\n");
	ps = ps_init(config);
	if (ps == NULL)
		exit(1);

	printf("micInit\n");

	if (cmd_ln_str_r(config, "-infile") != NULL) {
		printf("File input is disabled. Exiting.\n");
		exit(1);
		//recognize_from_file();
	}
	else {

		/* Make sure we exit cleanly (needed for profiling among other things) */
		/* Signals seem to be broken in arm-wince-pe. */
#if !defined(GNUWINCE) && !defined(_WIN32_WCE) && !defined(__SYMBIAN32__)
		signal(SIGINT, &sighandler);
#endif

		if (setjmp(jbuf) == 0) {
			microphoneInit(md);
			//recognize_from_microphone();
		}
	}
}

void
continuous_exit(mic_data_t &md)
{
	cont_ad_close(md.cont);
	ad_close(md.ad);
	ps_free(ps);
}