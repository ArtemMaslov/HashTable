#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#include "HashTable_Hash.h"
#include "_hashTable_private.h"

#include "HashTable_Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int HashTableConstructor(HashTable*   table,
						 const size_t listCount,
						 const size_t listCapacity,
						 size_t (*hashFunction)(const ListType*))
{
	LOG_HASH_TABLE_TRACE_CTOR;

	assert(table);
	assert(hashFunction);

	HASH_TABLE_ASSERT_STATUS;

	if ((table->Status = HashTableVerifyInit(table)) != HASH_TABLE_ERR_NO_ERRORS)
		return table->Status;

	table->Status    = HASH_TABLE_ERR_NO_ERRORS;
	table->ExtStatus = HASH_TABLE_ERR_NO_ERRORS;
	table->Warnings  = HASH_TABLE_WRN_NO_WARNINGS;

	table->ListCount = listCount;
	table->Lists     = (List*)calloc(sizeof(List), listCount);

	table->HashFunction  = hashFunction;

	if (!table->Lists)
	{
		LOG_HASH_TABLE_ERR_MEMORY;

		table->Status |= HASH_TABLE_ERR_MEMORY;

		return table->Status;
	}

	for (size_t st = 0; st < table->ListCount; st++)
	{
		if (ListConstructor(table->Lists + st, listCapacity) != LIST_ERR_NO_ERRORS)
		{
			LOG_F_HASH_TABLE_ERR("Ошибка создания массива списков в конструкторе. "
								 "Создано списков %zd.", st);

			table->ListCount = st;

			table->Status |= HASH_TABLE_ERR_LIST;

			HashTableDestructor(table);
			break;
		}
	}

	return HASH_TABLE_ERR_NO_ERRORS;
}

int HashTableDestructor(HashTable* table)
{
	LOG_HASH_TABLE_TRACE_CTOR;

	assert(table);

	HASH_TABLE_ASSERT_STATUS;

	int status = HASH_TABLE_ERR_NO_ERRORS;

	for (size_t st = 0; st < table->ListCount; st++)
	{
		ListDestructor(table->Lists + st);
	}

	free(table->Lists);

	return status;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int HashTableInsert(HashTable* table, const ListType* element)
{
	LOG_HASH_TABLE_TRACE_FUNC_0;

	assert(table);
	assert(element);

	HASH_TABLE_ASSERT_STATUS;

	size_t listIndex = 0;

	__asm
	{
		mov	ecx, dword ptr element[0]

		xor eax, eax
		crc32 eax, dword ptr[ecx]

		crc32 eax, dword ptr[ecx + 4]

		crc32 eax, dword ptr[ecx + 8]

		crc32 eax, dword ptr[ecx + 12]

		mov ebx, table
		mov ebx, dword ptr[ebx + 4] ; table->ListCount

		xor edx, edx
		div ebx

		mov listIndex, edx
	}

	size_t elemIndex = ListFind(table->Lists + listIndex, element);

	if (elemIndex != 0)
	{
		table->Warnings = HASH_TABLE_WRN_INSERT_EXIST;
		return table->Warnings;
	}

	if (ListAddElemAfter(table->Lists + listIndex, element, table->Lists[listIndex].Tail) != LIST_ERR_NO_ERRORS)
	{
		LOG_F_HASH_TABLE_ERR("Ошибка добавления элемента в список. "
							 "listIndex = %zd. "
							 "wordData = \"%16s\"", listIndex, (char*)element);

		table->ExtStatus = table->Lists[listIndex].Status;
		table->Status = HASH_TABLE_ERR_LIST;

		return table->Status;
	}

	return table->Status;
}

int HashTableRemove(HashTable* table, const ListType* element)
{
	LOG_HASH_TABLE_TRACE_FUNC_0;

	assert(table);
	assert(element);

	HASH_TABLE_ASSERT_STATUS;

	size_t listIndex = 0;

	__asm
	{
		mov	ecx, dword ptr element[0]

		xor eax, eax
		crc32 eax, dword ptr[ecx]

		crc32 eax, dword ptr[ecx + 4]

		crc32 eax, dword ptr[ecx + 8]

		crc32 eax, dword ptr[ecx + 12]

		mov ebx, table
		mov ebx, dword ptr[ebx + 4]; table->ListCount

		xor edx, edx
		div ebx

		mov listIndex, edx
	}

	size_t elemIndex = ListFind(table->Lists + listIndex, element);

	if (elemIndex == 0)
	{
		table->Warnings = HASH_TABLE_WRN_REMOVE_VOID;
		return table->Warnings;
	}

	if (ListRemoveElem(table->Lists + listIndex, elemIndex) != LIST_ERR_NO_ERRORS)
	{
		LOG_F_HASH_TABLE_ERR("Ошибка удаления элемента из списка. "
							 "listIndex = %zd. "
							 "wordData = \"%16s\"", listIndex, (char*)element);

		table->ExtStatus = table->Lists[listIndex].Status;
		table->Status = HASH_TABLE_ERR_LIST;

		return table->Status;
	}

	return table->Status;
}

ListType* HashTableFind(const HashTable* table, const ListType* element)
{
	LOG_HASH_TABLE_TRACE_FUNC_0;

	assert(table);
	assert(element);

	HASH_TABLE_ASSERT_STATUS;

	size_t listIndex = 0;

	__asm
	{
		mov	ecx, dword ptr element[0]

		xor eax, eax
		crc32 eax, dword ptr[ecx]

		crc32 eax, dword ptr[ecx + 4]

		crc32 eax, dword ptr[ecx + 8]

		crc32 eax, dword ptr[ecx + 12]

		mov ebx, table
		mov ebx, dword ptr[ebx + 4]; table->ListCount

		xor edx, edx
		div ebx

		mov listIndex, edx
	}

	size_t findIndex = ListFind(table->Lists + listIndex, element);

	if (findIndex == 0)
		return nullptr;

	return &table->Lists[listIndex].Nodes[findIndex].Data;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\