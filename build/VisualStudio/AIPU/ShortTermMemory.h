#pragma once

#include <iostream>
#include <time.h>
#include <chrono>

#include "STMRecord.h"

using namespace std;

const int SHORT_TERM_MEMORY_SIZE = 1024;


enum AIPUSTATE {
	IDLE = 0,
	SOUND_DETECTED,
	LOCATING_SPEAKER,
	AWAITING_KICKOFF_PHRASE,
	ENGAGED_IN_COVERSATION,
	CHARGING_BATTERY,
	PROCESSING_DATA
};


class ShortTermMemory
{
	STMRecord *STM[SHORT_TERM_MEMORY_SIZE];

	AIPUSTATE currentAIPUState;
	steady_clock::time_point timeStampOfLastAIPUStateSet;

public:
	ShortTermMemory();
	~ShortTermMemory();

	bool inputRecord(STMRecord*);
	bool deleteRecord(int index);
	bool markRecordAsProcessed(int index);
	int getSTMSize();
	STMRecord * getSTMRecord(int index);

	void setCurrentAIPUState(AIPUSTATE stateToSet)
	{
		currentAIPUState = stateToSet;
		timeStampOfLastAIPUStateSet = steady_clock::now();
	}
	AIPUSTATE getCurrentAIPUState()
	{
		return currentAIPUState;
	}
	int getLastAIPUStateChangeTimeRelativeToNowInMilliSeconds()
	{
		steady_clock::time_point currentTime = steady_clock::now(); //currrent time of running this function
		return duration_cast<milliseconds>(currentTime - timeStampOfLastAIPUStateSet).count();
	}
	STMRecord * getLatestUnprocessedRecord(STMRecordType ofRecordType ) //gets latest record of a certain type  but ignores if it is processed already or if it was created after the last AIPU state has changed
	{
		STMRecord *tempReadRecord = NULL;
		for (int i = 0; i < SHORT_TERM_MEMORY_SIZE ; i++)
		{
			tempReadRecord = STM[i];
			if (tempReadRecord == NULL || tempReadRecord->processed) // this makes sure that the record we are processing has not been already processed
				continue;
			if (tempReadRecord->getTimeRelativeToNowInMilliSeconds() > getLastAIPUStateChangeTimeRelativeToNowInMilliSeconds())
				//this makes sure that the record we are processing did not exist before the last AIPU state change. In order for this to be effective, you must always reset the AIPU state after processing an actual record
				continue;
			if (tempReadRecord->recordType == ofRecordType)
				return tempReadRecord;
		}
		return NULL;
	}

};
