#include "ShortTermMemory.h"


ShortTermMemory::ShortTermMemory()
{
	for (int i = 0; i < SHORT_TERM_MEMORY_SIZE; i++)
	{
		STM[i] = NULL;
	}
}


ShortTermMemory::~ShortTermMemory()
{
}

bool ShortTermMemory::inputRecord(STMRecord* inputRecord)
{
	delete STM[SHORT_TERM_MEMORY_SIZE - 1]; // delete last entry in the stack
	STM[SHORT_TERM_MEMORY_SIZE - 1] = NULL; // delete last entry in the stack

	//shift all records down the array so that the latest input record takes index 0  in the array
	for (int i = SHORT_TERM_MEMORY_SIZE - 1 ; i > 0; i--)
	{
		STM[i] = STM[i-1];
	}

	STM[0] = inputRecord;

	return true;
}

bool ShortTermMemory::deleteRecord(int index)
{
	delete STM[index];

	if (index == (SHORT_TERM_MEMORY_SIZE - 1)) //if record to delete is the last one, operation can end here.
	{
		STM[index] = NULL;
		return true;
	}

	STM[index] = STM[index + 1];

	for (int i = index + 1; i < SHORT_TERM_MEMORY_SIZE- 1; i++)
	{
		STM[i] = STM[i + 1];
	}

	STM[SHORT_TERM_MEMORY_SIZE-1] = NULL;

	return true;
}

int ShortTermMemory::getSTMSize()
{
	return SHORT_TERM_MEMORY_SIZE;
}

STMRecord * ShortTermMemory::getSTMRecord(int index)
{
	return STM[index];
}


bool ShortTermMemory::markRecordAsProcessed(int index)
{
	if (STM[index] == NULL)
	{
		return false;
	}
	else
	{
		STM[index]->processed = true;
		return true;
	}
}