#pragma once

#include <iostream>
#include <time.h>

#include "STMRecord.h"

using namespace std;

const int SHORT_TERM_MEMORY_SIZE = 1024;

class ShortTermMemory
{
	STMRecord *STM[SHORT_TERM_MEMORY_SIZE];
public:
	ShortTermMemory();
	~ShortTermMemory();

	bool inputRecord(STMRecord*);
	bool deleteRecord(int index);
	bool markRecordAsProcessed(int index);
	int getSTMSize();
	STMRecord * getSTMRecord(int index);
	

};
