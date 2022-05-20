#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "HashTable.h"
#include "HashTable_Hash.h"
#include "HashTable_UnitTests.h"

#include "HashTable_Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Добавить все слова из Text (текст должен быть предварительно разбит на слова).
 *
 * @param table Указатель на хеш-таблицу.
 * @param text  Указатель на структуру Text.
*/
static void HashTableLoadWordsIntoTable(HashTable* table, Text* text);

#define CLEAR_AND_RETURN goto clear_and_return

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

void TestHashTable_Sheakspear()
{
	HashTable table = {};

	Text text = {};

	const size_t functionsCount = 6;

	size_t (*hashFunctions[functionsCount])(const ListType*) =
	{
		HashTable_HashConstant,
		HashTable_HashLetter,
		HashTable_HashLength,
		HashTable_HashCharSum,
		HashTableHash_Ror,
		HashTableHash_CRC32_C
	};

	size_t* hash_data = nullptr;

	FILE*   outFile   = nullptr;

	HashTableConstructor(&table, DefaultListCount, DefaultListCapacity, HashTableHash_CRC32_C);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextConstructor(&text, DefaultWordsCapacity);

	if (text.Status != TEXT_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextParseIntoWordsDir(&text, "tests\\*.txt", 32);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	outFile = fopen("hash_statistic_list.csv", "w");

	if (!outFile)
		CLEAR_AND_RETURN;

	hash_data = (size_t*)calloc(functionsCount * table.ListCount, sizeof(size_t));

	if (!hash_data)
		CLEAR_AND_RETURN;

	{
		const size_t listCount = table.ListCount;

		for (size_t funcIndex = 0; funcIndex < functionsCount; funcIndex++)
		{
			table.HashFunction = hashFunctions[funcIndex];

			HashTableLoadWordsIntoTable(&table, &text);

			printf("Hash function %zd loaded.\n", funcIndex + 1);

			for (size_t listIndex = 0; listIndex < listCount; listIndex++)
			{
				hash_data[funcIndex * listCount + listIndex] = table.Lists[listIndex].Size;
			}

			HashTableClearLists(&table);
		}

		for (size_t funcIndex = 0; funcIndex < functionsCount; funcIndex++)
			fprintf(outFile, "hash%zd, ", funcIndex + 1);

		fputc('\n', outFile);

		for (size_t listIndex = 0; listIndex < table.ListCount; listIndex++)
		{
			for (size_t funcIndex = 0; funcIndex < functionsCount; funcIndex++)
				fprintf(outFile, "%zd, ", hash_data[funcIndex * listCount + listIndex]);

			fputc('\n', outFile);
		}
	}

clear_and_return:

	free(hash_data);
	HashTableDestructor(&table);
	TextDestructor(&text);
}

void TestHashTable_OptimizationFind()
{
	HashTable table = {};

	Text      text  = {};

	HashTableConstructor(&table, DefaultListCount, DefaultListCapacity, HashTable_CRC32_Intrin);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextConstructor(&text, DefaultWordsCapacity);

	if (text.Status != TEXT_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextParseIntoWordsDir(&text, "tests\\*.txt", MaximumWordSize);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	HashTableLoadWordsIntoTable(&table, &text);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	{
		const size_t wordsCount = text.WordsSize;

		for (size_t st1 = 0; st1 < 500; st1++)
		{
			for (size_t st = 0; st < wordsCount; st++)
			{
				Word* word = HashTableFind(&table, text.Words + st);

				if (word == nullptr)
				{
					puts("Error");
					CLEAR_AND_RETURN;
				}
			}
			printf("%zd\n", st1);
		}
	}

clear_and_return:

	HashTableDestructor(&table);
	TextDestructor(&text);
}

void TestHashTable_OptimizationInsertRemove()
{
	HashTable table = {};

	Text      text  = {};

	HashTableConstructor(&table, DefaultListCount, DefaultListCapacity, HashTable_CRC32_Intrin);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextConstructor(&text, DefaultWordsCapacity);

	if (text.Status != TEXT_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextParseIntoWordsDir(&text, "tests\\*.txt", MaximumWordSize);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	HashTableLoadWordsIntoTable(&table, &text);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	{
		const size_t wordsCount = text.WordsSize;

		for (size_t st = 0; st < 50; st++)
		{
			for (size_t st = 0; st < wordsCount; st++)
			{
				HashTableRemove(&table, text.Words + st);
			}

			for (size_t st = 0; st < wordsCount; st++)
			{
				HashTableInsert(&table, text.Words + st);
			}

			printf("%zd\n", st);
		}
	}

clear_and_return:

	HashTableDestructor(&table);
	TextDestructor(&text);
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

static void HashTableLoadWordsIntoTable(HashTable* table, Text* text)
{
	LOG_HASH_TABLE_TRACE_FUNC_1;

	assert(table);
	assert(text);

	HASH_TABLE_ASSERT_STATUS;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	size_t wordsCount = text->WordsSize;
	Word*  words      = text->Words;

	for (size_t st = 0; st < wordsCount; st++)
	{
		HashTableInsert(table, words + st);

		if (table->Status != HASH_TABLE_ERR_NO_ERRORS)
			return;
	}

	LOG_HASH_TABLE_DBG("Data loaded");
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\