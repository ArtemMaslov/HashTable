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

struct WordsArray128
{
	// Массив слов.
	__m128i* Data;

	// Размер массива
	size_t Size;
};

const size_t TextsCount = 42;

/**
 * @brief Добавить все слова из TextAnalyzer (текст должен быть предварительно разбит на слова).
 *
 * @param table Указатель на хеш-таблицу.
 * @param words Указатель на массив слов.
*/
static void HashTableLoadWordsIntoTable(HashTable* table, WordsArray128* words);

/**
 * @brief Переводит слова из структуры Text в массив __m128i.
 * 
 * @param words Указатель на массив слов.
 * @param text  Указатель на структуру TextAnalyzer.
 * 
 * @return HashTableError.
*/
static int ConvertWordsType(WordsArray128* words, TextAnalyzer* text);

/**
 * @brief Очищает массив слов __m128i.
 * 
 * @param words Указатель на массив слов.
*/
static void WordsArrayDestructor(WordsArray128* words);

/**
 * @brief Добавить все слова из текстов в хеш-таблицу.
 * 
 * @param table Указатель на хеш-таблицу.
 * @param text  Указатель на структуру TextAnalyzer.
*/
static void HashTableLoadWordsIntoTable(HashTable* table, TextAnalyzer* text);

#define CLEAR_AND_RETURN goto clear_and_return

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

void TestHashTable_Sheakspear()
{
	HashTable     table = {};

	TextAnalyzer  text  = {};

	WordsArray128 words = {};

	const size_t functionsCount = 6;

	size_t (*hashFunctions[functionsCount])(const ListType*) =
	{
		HashTable_HashConstant,
		HashTable_HashLetter,
		HashTable_HashLength,
		HashTable_HashCharSum,
		HashTable_HashRor,
		HashTable_HashCRC32_C
	};

	size_t* hash_data = nullptr;

	FILE*   outFile   = nullptr;

	HashTableConstructor(&table, DefaultListCount, DefaultListCapacity, HashTable_HashCRC32_C);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextConstructor(&text, DefaultWordsCapacity, TextsCount);

	if (text.Status != TEXT_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextParseIntoWordsDirectory(&text, "tests\\*.txt", 32);

	if (text.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	if (ConvertWordsType(&words, &text) != HASH_TABLE_ERR_NO_ERRORS)
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

			HashTableLoadWordsIntoTable(&table, &words);

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
	WordsArrayDestructor(&words);
}

void TestHashTable_OptimizationFind()
{
	HashTable     table = {};

	TextAnalyzer  text  = {};

	WordsArray128 words = {};

	HashTableConstructor(&table, DefaultListCount, DefaultListCapacity, HashTable_HashCRC32_C);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextConstructor(&text, DefaultWordsCapacity, TextsCount);

	if (text.Status != TEXT_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextParseIntoWordsDirectory(&text, "tests\\*.txt", MaximumWordSize);

	if (ConvertWordsType(&words, &text) != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	HashTableLoadWordsIntoTable(&table, &words);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	{
		const size_t wordsCount = words.Size;
	
		for (size_t st1 = 0; st1 < 1000; st1++)
		{
			for (size_t st = 0; st < wordsCount; st++)
			{
				__m128i* word = HashTableFind(&table, &words.Data[st]);

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
	WordsArrayDestructor(&words);
}

void TestHashTable_OptimizationInsertRemove()
{
	HashTable     table = {};

	TextAnalyzer  text  = {};

	WordsArray128 words = {};

	HashTableConstructor(&table, DefaultListCount, DefaultListCapacity, HashTable_HashCRC32_C);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextConstructor(&text, DefaultWordsCapacity, TextsCount);

	if (text.Status != TEXT_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	TextParseIntoWordsDirectory(&text, "tests\\*.txt", MaximumWordSize);

	if (ConvertWordsType(&words, &text) != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	HashTableLoadWordsIntoTable(&table, &words);

	if (table.Status != HASH_TABLE_ERR_NO_ERRORS)
		CLEAR_AND_RETURN;

	{
		const size_t wordsCount = words.Size;

		for (size_t st1 = 0; st1 < 1000; st1++)
		{
			for (size_t st = 0; st < wordsCount; st++)
			{
				HashTableRemove(&table, &words.Data[st]);
			}

			for (size_t st = 0; st < wordsCount; st++)
			{
				HashTableInsert(&table, &words.Data[st]);
			}

			printf("%zd\n", st1);
		}
	}

clear_and_return:

	HashTableDestructor(&table);
	TextDestructor(&text);
	WordsArrayDestructor(&words);
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

static void HashTableLoadWordsIntoTable(HashTable* table, WordsArray128* words)
{
	LOG_HASH_TABLE_TRACE_FUNC_1;

	assert(table);
	assert(words);

	HASH_TABLE_ASSERT_STATUS;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	const size_t wordsSize = words->Size;

	const __m128i* data = words->Data;

	for (size_t st = 0; st < wordsSize; st++)
	{
		HashTableInsert(table, data + st);

		if (table->Status != HASH_TABLE_ERR_NO_ERRORS)
			return;
	}

	LOG_HASH_TABLE_DBG("Data loaded");
}

static int ConvertWordsType(WordsArray128* words, TextAnalyzer* text)
{
	LOG_HASH_TABLE_TRACE_FUNC_1;

	assert(words);
	assert(text);

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	const size_t wordsSize = text->WordsSize;

	const Word* textWords  = text->Words;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	__m128i* wordsArray = (__m128i*)calloc(wordsSize, sizeof(__m128i));

	if (!wordsArray)
	{
		LOG_HASH_TABLE_ERR_MEMORY;

		return HASH_TABLE_ERR_MEMORY;
	}

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	for (size_t st = 0; st < wordsSize; st++)
	{
		__m128i word = _mm_set1_epi32(0);

		memcpy(&word, textWords[st].Data, textWords[st].Size);

		wordsArray[st] = word;
	}

	words->Data = wordsArray;
	words->Size = wordsSize;

	return HASH_TABLE_ERR_NO_ERRORS;
}

static void WordsArrayDestructor(WordsArray128* words)
{
	assert(words);

	free(words->Data);

	words->Data = nullptr;
	words->Size = 0;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\