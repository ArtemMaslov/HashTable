#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"
#include "_hashTable_private.h"

#include "HashTable_Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int HashTableVerifyInit(const HashTable* table)
{
	assert(table);

	//HASH_TABLE_ASSERT_STATUS;

	if (table->Status    != HASH_TABLE_ERR_NO_ERRORS ||
		table->ExtStatus != 0 ||
		table->ListCount != 0 ||
		table->Lists     != nullptr)
	{
		return HASH_TABLE_ERR_INIT;
	}
	else
	{
		return HASH_TABLE_ERR_NO_ERRORS;
	}
}