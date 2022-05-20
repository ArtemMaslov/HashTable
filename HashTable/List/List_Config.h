#ifndef LIST_CONFIG_H
#define LIST_CONFIG_H

#include <string.h>
#include <emmintrin.h>
#include <smmintrin.h>

#include "..\FileIO.h"

#include "..\Text\Text.h"
#include "List.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

const size_t MaximumWordSize = 32;

/// @brief ��� ��������� ������
/// �������� �� ��� ���������, ������� ����� ������������ ������
typedef Word ListType;

/// �����, � ������� ����� �������� ����������� ��� ����������� �����.
#define LIST_LOG_IMAGE_FOLDER "_listImgs\\"

/// �������� �������� ��������� ������ � ������� assert.
#define LIST_ENABLE_ASSERT_STATUS true

#if LIST_ENABLE_ASSERT_STATUS
/// ��������� ��������� ������.
#define LIST_ASSERT_STATUS assert(list->Status == LIST_ERR_NO_ERRORS)
#else
/// ��������� ��������� ������.
#define LIST_ASSERT_STATUS ((void)0)
#endif

/// �����������, �� ������� ���������� ��������������� ������ ��� ����������.
const double ListResizeCoef = 2;

/**
 * @brief      ���������� ��� �������� ������.
 * 
 * @param val1 ������ �������.
 * @param val2 ������ �������.
 * 
 * @return     true, ���� �������� �����. false, ���� �������� ��������.
*/
static inline bool ListComparator(const ListType val1, const ListType val2)
{
	if (val1.Size != val2.Size)
		return false;

	size_t maxSize = val1.Size > val2.Size? val1.Size : val2.Size;

	return strncmp(val1.Data, val2.Data, maxSize) == 0;

	//return memcmp(&val1, &val2, sizeof(ListType)) == 0;
}

/// ������ ������ �������������� �������� � ������.
const size_t ListToStringSize = 32;

/**
 * @brief        ������������� � ������ ������� ������.
 * 
 * @param buffer ����� �������� ������.
 * @param value  ������� ������.
*/
static inline void ListElementToString(char* buffer, const size_t bufferSize, const ListType* value)
{
	snprintf(buffer, bufferSize, "%*s", (unsigned int)MaximumWordSize, (char*)value);

	buffer[MaximumWordSize + 1] = '\0';
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif // !LIST_CONFIG_H