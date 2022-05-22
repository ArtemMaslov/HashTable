#ifndef HASH_TABLE_HASH_H
#define HASH_TABLE_HASH_H

#include "HashTable.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Всегда постоянная хеш-функция. Равна 1 для любого элемента.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashConstant(const ListType* element);

/**
 * @brief ASCII-код первой буквы.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashLetter(const ListType* element);

/**
 * @brief Длина слова.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashLength(const ListType* element);

/**
 * @brief Сумма ASCII-кодов букв.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashCharSum(const ListType* element);

/**
 * @brief Циклический сдвиг вправо.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashRor(const ListType* element);

/**
 * @brief CRC-32, реализация на C.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashCRC32_C(const ListType* element);

/**
 * @brief CRC-32, реализация с помощью intrinsic function.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
size_t HashTable_HashCRC32_Intrin(const ListType* element);

/**
 * @brief CRC-32, ассемблерная реализация.
 *
 * @param element Указатель на элемент хеш-таблицы.
 *
 * @return Значение хеш-функции. Не ограничено размером хеш-таблицы.
*/
extern "C" size_t HashTable_HashCRC32_Asm(const ListType* element);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif