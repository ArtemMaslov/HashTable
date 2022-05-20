#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <nmmintrin.h>

#include "HashTable.h"
#include "_hashTable_private.h"

#include "HashTable_Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

size_t CalcHash(const HashTable* table, const ListType* element)
{
	assert(table);
	assert(element);

	return table->HashFunction(element) % table->ListCount;
}

size_t HashTable_HashConstant(const ListType* element)
{
	assert(element);

	return 1;
}

size_t HashTable_HashLetter(const ListType* element)
{
	assert(element);

	return ((char*)element)[0];
}

size_t HashTable_HashLength(const ListType* element)
{
	assert(element);

	return strnlen((char*)element, 16);
}

size_t HashTable_HashCharSum(const ListType* element)
{
	assert(element);

	const char* data = (char*)element;

	size_t hash = 0;

	for (size_t st = 0; *data && st < 16; st++)
		hash += data[st];

	return hash;
}

size_t HashTableHash_Ror(const ListType* element)
{
	assert(element);

	const char* data = (char*)element;

	size_t hash =  (unsigned char)data[0];

	for (size_t st = 1; *data && st < 16; st++)
	{
		hash = ((hash & 1) << (8 * sizeof(size_t) - 1)) | (hash >> 1);

		hash ^= (unsigned char)data[st];
	}

	return hash;
}

size_t HashTableHash_CRC32_C(const ListType* element)
{
	assert(element);

	static bool inited = false;
	static size_t crc_table[256] = { 0 };
	size_t hash = 0;

	if (!inited)
	{
		inited = true;
		for (int i = 0; i < 256; i++)
		{
			hash = i;
			for (int j = 0; j < 8; j++)
				hash = hash & 1 ? (hash >> 1) ^ 0xEDB88320UL : hash >> 1;

			crc_table[i] = hash;
		};
	}

	hash = 0xFFFFFFFFUL;

	const char*  data = (const char*)element;

	for (size_t st = 0; st < 16; st++)
		hash = crc_table[(hash ^ data[st]) & 0xFF] ^ (hash >> 8);

	return (hash ^ 0xFFFFFFFFUL);
}

size_t HashTable_CRC32_Intrin(const ListType* element)
{
	assert(element);

	uint64_t crc = 0;
	crc = _mm_crc32_u64(crc, ((uint64_t*)element)[0]);

	return _mm_crc32_u64(crc, ((uint64_t*)element)[1]);
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\