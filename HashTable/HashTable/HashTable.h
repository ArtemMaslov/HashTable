#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "..\Text\Text.h"
#include "..\List\List.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/// Стандартный размер хеш-таблицы - количество списков в ней.
const size_t DefaultListCount = 15013;
/// Стандартная вместительность списков.
const size_t DefaultListCapacity = 1000;
/// Стандартное количество слов для структуры TextAnalyzer.
const size_t DefaultWordsCapacity = 1000000;

struct HashTable
{
	/// Указатель на хеш-функцию.
	size_t   (*HashFunction)(const ListType*);

	/// Количество списков.
	size_t   ListCount;
	/// Массив списков.
	List*    Lists;

	/// Код состояния таблицы
	int      Status;
	/// Код состояния модулей, вызываемых из таблицы, в случае ошибки.
	int      ExtStatus;
	/// Предупреждения работы хеш-таблицы, не критичны.
	int      Warnings;
};

/// Критические ошибки в работе хеш-таблицы, выполнение функции прерывается.
enum HashTableErrors
{
	/// Ошибок нет.
	HASH_TABLE_ERR_NO_ERRORS = 0,

	/// Ошибка выделения памяти.
	HASH_TABLE_ERR_MEMORY    = 1 << 1,
	/// Ошибка работы с файлом.
	HASH_TABLE_ERR_FILE      = 1 << 2,
	/// При инициализации таблица не была очищена.
	HASH_TABLE_ERR_INIT      = 1 << 3,

	// Ошибки в модулях.

	/// Ошибка в списке.
	HASH_TABLE_ERR_LIST      = 1 << 20,
	/// Ошибка ввода-вывода в файл.
	HASH_TABLE_ERR_FILE_IO   = 1 << 21,
};

/// Предупреждения. Выполнение функции продолжается.
enum HashTableWarnings
{
	/// Нет предупреждений.
	HASH_TABLE_WRN_NO_WARNINGS  = 0,

	/// Попытка вставить существующий элемент. 
	HASH_TABLE_WRN_INSERT_EXIST = 1 << 0,
	/// Попытка удалить не существующий элемент.
	HASH_TABLE_WRN_REMOVE_VOID  = 1 << 1,
};

/// Включить проверку состояния таблицы с помощью assert.
#define HASH_TABLE_ENABLE_ASSERT_STATUS true

#if HASH_TABLE_ENABLE_ASSERT_STATUS
/// Проверить состояние таблицы.
#define HASH_TABLE_ASSERT_STATUS assert(table->Status == HASH_TABLE_ERR_NO_ERRORS)
#else
/// Проверить состояние таблицы.
#define HASH_TABLE_ASSERT_STATUS ((void)0)
#endif

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Конструктор хеш-таблицы.
 * 
 * @param table        Указатель на хеш-таблицу.
 * @param listCount    Размер хеш-таблицы.
 * @param listCapacity Вместительность списков.
 * @param hashFunction Указатель на хеш-функцию.
 * 
 * @return HashTableErrors.
*/
int HashTableConstructor(HashTable* table,
						 const size_t listCount,
						 const size_t listCapacity,
						 size_t (*hashFunction)(const ListType*));

/**
 * @brief Деструктор хеш-таблицы.
 * 
 * @param table Указатель на хеш-таблицу.
 * 
 * @return HashTableErrors.
*/
int HashTableDestructor(HashTable* table);

/**
 * @brief Добавить элемент в хеш-таблицу.
 * 
 * @param table Указатель на хеш-таблицу.
 * @param word  Указатель на элемент.
 * 
 * @return HashTableErrors.
*/
int HashTableInsert(HashTable* table, const ListType* word);

/**
 * @brief Найти элемент в хеш-таблице.
 * 
 * @param table Указатель на хеш-таблицу.
 * @param word  Указатель на элемент.
 * 
 * @return  Указатель на элемент. nullptr, если элемент не был найден.
*/
ListType* HashTableFind(const HashTable* table, const ListType* word);

/**
 * @brief Удалить элемент из хеш-таблицы.
 * 
 * @param table Указатель на хеш-таблицу.
 * @param word  Указатель на элемент.
 * 
 * @return HashTableErrors.
*/
int HashTableRemove(HashTable* table, const ListType* word);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Очистить списки хеш-таблицы.
 * 
 * @param table Указатель на хеш-таблицу.
*/
void HashTableClearLists(HashTable* table);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif // !HASH_TABLE_H