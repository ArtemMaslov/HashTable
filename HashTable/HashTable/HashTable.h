#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "..\Text\Text.h"
#include "..\List\List.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/// ����������� ������ ���-������� - ���������� ������� � ���.
const size_t DefaultListCount = 1500;
/// ����������� ��������������� �������.
const size_t DefaultListCapacity = 1000;
/// ����������� ���������� ���� ��� ��������� Text.
const size_t DefaultWordsCapacity = 1000000;

struct HashTable
{
	/// ��������� �� ���-�������.
	size_t   (*HashFunction)(const ListType*);

	/// ���������� �������.
	size_t   ListCount;
	/// ������ �������.
	List*    Lists;

	/// ��� ��������� �������
	int      Status;
	/// ��� ��������� �������, ���������� �� �������, � ������ ������.
	int      ExtStatus;
	/// �������������� ������ ���-�������, �� ��������.
	int      Warnings;
};

/// ����������� ������ � ������ ���-�������, ���������� ������� �����������.
enum HashTableErrors
{
	/// ������ ���.
	HASH_TABLE_ERR_NO_ERRORS = 0,

	/// ������ ��������� ������.
	HASH_TABLE_ERR_MEMORY    = 1 << 1,
	/// ������ ������ � ������.
	HASH_TABLE_ERR_FILE      = 1 << 2,
	/// ��� ������������� ������� �� ���� �������.
	HASH_TABLE_ERR_INIT      = 1 << 3,

	// ������ � �������.

	/// ������ � ������.
	HASH_TABLE_ERR_LIST      = 1 << 20,
	/// ������ �����-������ � ����.
	HASH_TABLE_ERR_FILE_IO   = 1 << 21,
};

/// ��������������. ���������� ������� ������������.
enum HashTableWarnings
{
	/// ��� ��������������.
	HASH_TABLE_WRN_NO_WARNINGS  = 0,

	/// ������� �������� ������������ �������. 
	HASH_TABLE_WRN_INSERT_EXIST = 1 << 0,
	/// ������� ������� �� ������������ �������.
	HASH_TABLE_WRN_REMOVE_VOID  = 1 << 1,
};

/// �������� �������� ��������� ������� � ������� assert.
#define HASH_TABLE_ENABLE_ASSERT_STATUS true

#if HASH_TABLE_ENABLE_ASSERT_STATUS
/// ��������� ��������� �������.
#define HASH_TABLE_ASSERT_STATUS assert(table->Status == HASH_TABLE_ERR_NO_ERRORS)
#else
/// ��������� ��������� �������.
#define HASH_TABLE_ASSERT_STATUS ((void)0)
#endif

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief ����������� ���-�������.
 * 
 * @param table        ��������� �� ���-�������.
 * @param listCount    ������ ���-�������.
 * @param listCapacity ��������������� �������.
 * @param hashFunction ��������� �� ���-�������.
 * 
 * @return HashTableErrors.
*/
int HashTableConstructor(HashTable* table,
						 const size_t listCount,
						 const size_t listCapacity,
						 size_t (*hashFunction)(const ListType*));

/**
 * @brief ���������� ���-�������.
 * 
 * @param table ��������� �� ���-�������.
 * 
 * @return HashTableErrors.
*/
int HashTableDestructor(HashTable* table);

/**
 * @brief �������� ������� � ���-�������.
 * 
 * @param table ��������� �� ���-�������.
 * @param word  ��������� �� �������.
 * 
 * @return HashTableErrors.
*/
int HashTableInsert(HashTable* table, const ListType* word);

/**
 * @brief ����� ������� � ���-�������.
 * 
 * @param table ��������� �� ���-�������.
 * @param word  ��������� �� �������.
 * 
 * @return  ��������� �� �������. nullptr, ���� ������� �� ��� ������.
*/
ListType* HashTableFind(const HashTable* table, const ListType* word);

/**
 * @brief ������� ������� �� ���-�������.
 * 
 * @param table ��������� �� ���-�������.
 * @param word  ��������� �� �������.
 * 
 * @return HashTableErrors.
*/
int HashTableRemove(HashTable* table, const ListType* word);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief �������� ������ ���-�������.
 * 
 * @param table ��������� �� ���-�������.
*/
void HashTableClearLists(HashTable* table);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif // !HASH_TABLE_H