#ifndef AIBOT_CONTINUOUS_H
#define AIBOT_CONTINUOUS_H

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>

#include "pocketsphinx.h"

class PocketSphinxArguments;

typedef struct {
	ad_rec_t *ad;
	int16 adbuf[4096];
	cont_ad_t *cont;
	char const *hyp;
	char const *uttid;
	float64 prob;
} mic_data_t;

void continuous_init(PocketSphinxArguments& arguments, mic_data_t &md);
void continuous_exit(mic_data_t &md);
void getUtterance(mic_data_t &md);

#endif