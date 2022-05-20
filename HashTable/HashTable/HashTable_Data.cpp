#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"
#include "_hashTable_private.h"

#include "HashTable_Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

void HashTableClearLists(HashTable* table)
{
	LOG_HASH_TABLE_TRACE_FUNC_1;

	assert(table);

	HASH_TABLE_ASSERT_STATUS;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	const size_t listCount = table->ListCount;

	for (size_t st = 0; st < listCount; st++)
	{
		ClearList(table->Lists + st);
	}
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\