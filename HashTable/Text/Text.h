#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

enum TextErrors
{
	/// Ошибок нет.
	TEXT_ERR_NO_ERRORS = 0,

	/// Ошибка выделения памяти.
	TEXT_ERR_MEMORY    = 1 << 1,

	/// Ошибка работы с файлом.
	TEXT_ERR_FILE      = 1 << 2,

	/// Попытка добавить текст при TextsSize == TextsCount.
	TEXT_ERR_OVERFLOW  = 1 << 3
};

/// Структура слова.
struct Word
{
	/// Указатель на строку, содержащую слово.
	/// Строка необязательно заканчивается '\0', главное правильно указать длину слова.
	char* Data;

	/// Длина слова.
	size_t Size;
};

struct Text
{
	/// Размер текста.
	size_t Size;
	/// Указатель на начало текста. Текст должен заканчиваться '\0'
	char*  Data;
};

struct TextAnalyzer
{
	/// Текущее количество текстов.
	size_t  TextsSize;
	/// Максимальное количество текстов.
	size_t  TextsCount;
	/// Тексты.
	Text*   Texts;

	/// Текущий размер массива, то есть текущее количество слов в массиве.
	size_t  WordsSize;
	/// Вместительность массива, размер доступной памяти.
	size_t  WordsCapacity;
	/// Массив слов.
	Word*   Words;

	/// Состояние структуры.
	int     Status;
};

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Конструктор текста.
 * 
 * @param text          Указатель на структуру TextAnalyzer.
 * @param wordsCapacity Ожидаемое количество слов в тексте.
 * 
 * @return TextErrors.
*/
int TextConstructor(TextAnalyzer* text, const size_t wordsCapacity, const size_t textsCount);

/**
 * @brief          Прочитать файл.
 *
 * @param text     Указатель на структуру TextAnalyzer.
 * @param fileName Имя файла.
*/
int TextReadFile(TextAnalyzer* text, const char* fileName);

/**
 * @brief Деструктор текста. Очищает всю структуру.
 * 
 * @param text Указатель на структуру TextAnalyzer.
*/
void TextDestructor(TextAnalyzer* text);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Разбить текст на слова и сохранить их в TextAnalyzer.Words.
 * 
 * @param text          Указатель на структуру TextAnalyzer.
 * @param maxWordLength Максимальная длина слова, слова большей длины игнорируются.
*/
void TextParseIntoWords(TextAnalyzer* text, const size_t maxWordLength);

/**
 * @brief Прочитать все файлы из директории, разбить прочитанные тексты на слова и
 * сохранить все слова в памяти.
 *
 * @param text            Указатель на структуру TextAnalyzer.
 * @param folderPath      Строка - путь к директории с файлами.
 * @param maximumWordSize Максимальная длина слова, слова большей длины игнорируются.
*/
void TextParseIntoWordsDirectory(TextAnalyzer* text, const char* folderPath, const size_t maximumWordSize);

/**
 * @brief Посчитать количество слов в тексте.
 *
 * @param text          Указатель на структуру TextAnalyzer.
 * @param maxWordLength Максимальная длина слова, слова большей длины игнорируются.
 *
 * @return Количество слов в тексте.
*/
size_t TextCountWords(const TextAnalyzer* text, const size_t maxWordLength);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif