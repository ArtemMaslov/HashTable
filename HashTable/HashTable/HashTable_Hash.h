#ifndef HASH_TABLE_HASH_H
#define HASH_TABLE_HASH_H

#include "HashTable.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief ������ ���������� ���-�������. ����� 1 ��� ������ ��������.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashConstant(const ListType* element);

/**
 * @brief ASCII-��� ������ �����.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashLetter(const ListType* element);

/**
 * @brief ����� �����.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashLength(const ListType* element);

/**
 * @brief ����� ASCII-����� ����.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashCharSum(const ListType* element);

/**
 * @brief ����������� ����� ������.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashRor(const ListType* element);

/**
 * @brief CRC-32, ���������� �� C.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashCRC32_C(const ListType* element);

/**
 * @brief CRC-32, ���������� � ������� intrinsic function.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
size_t HashTable_HashCRC32_Intrin(const ListType* element);

/**
 * @brief CRC-32, ������������ ����������.
 *
 * @param element ��������� �� ������� ���-�������.
 *
 * @return �������� ���-�������. �� ���������� �������� ���-�������.
*/
extern "C" size_t HashTable_HashCRC32_Asm(const ListType* element);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif