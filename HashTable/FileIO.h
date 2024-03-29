#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief      Проверяет, существует ли директория.
 *
 * @param path Путь к директории.
 *
 * @return     true, если директория существует.
*/
bool DirectoryExist(const char* path);

/**
 * @brief      Получить размер файла.
 *
 * @param file Указатель на открытый файл.
 *
 * @return	   Размер файла.
*/
size_t GetFileSize(FILE* file);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif // !FILE_IO_H