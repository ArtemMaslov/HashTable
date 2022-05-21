#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

enum TextErrors
{
	/// ������ ���.
	TEXT_ERR_NO_ERRORS = 0,

	/// ������ ��������� ������.
	TEXT_ERR_MEMORY    = 1 << 1,

	/// ������ ������ � ������.
	TEXT_ERR_FILE      = 1 << 2,

	/// ������� �������� ����� ��� TextsSize == TextsCount.
	TEXT_ERR_OVERFLOW  = 1 << 3
};

/// ��������� �����.
struct Word
{
	/// ��������� �� ������, ���������� �����.
	/// ������ ������������� ������������� '\0', ������� ��������� ������� ����� �����.
	char* Data;

	/// ����� �����.
	size_t Size;
};

struct Text
{
	/// ������ ������.
	size_t Size;
	/// ��������� �� ������ ������. ����� ������ ������������� '\0'
	char*  Data;
};

struct TextAnalyzer
{
	/// ������� ���������� �������.
	size_t  TextsSize;
	/// ������������ ���������� �������.
	size_t  TextsCount;
	/// ������.
	Text*   Texts;

	/// ������� ������ �������, �� ���� ������� ���������� ���� � �������.
	size_t  WordsSize;
	/// ��������������� �������, ������ ��������� ������.
	size_t  WordsCapacity;
	/// ������ ����.
	Word*   Words;

	/// ��������� ���������.
	int     Status;
};

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief ����������� ������.
 * 
 * @param text          ��������� �� ��������� TextAnalyzer.
 * @param wordsCapacity ��������� ���������� ���� � ������.
 * 
 * @return TextErrors.
*/
int TextConstructor(TextAnalyzer* text, const size_t wordsCapacity, const size_t textsCount);

/**
 * @brief          ��������� ����.
 *
 * @param text     ��������� �� ��������� TextAnalyzer.
 * @param fileName ��� �����.
*/
int TextReadFile(TextAnalyzer* text, const char* fileName);

/**
 * @brief ���������� ������. ������� ��� ���������.
 * 
 * @param text ��������� �� ��������� TextAnalyzer.
*/
void TextDestructor(TextAnalyzer* text);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief ������� ����� �� ����� � ��������� �� � TextAnalyzer.Words.
 * 
 * @param text          ��������� �� ��������� TextAnalyzer.
 * @param maxWordLength ������������ ����� �����, ����� ������� ����� ������������.
*/
void TextParseIntoWords(TextAnalyzer* text, const size_t maxWordLength);

/**
 * @brief ��������� ��� ����� �� ����������, ������� ����������� ������ �� ����� �
 * ��������� ��� ����� � ������.
 *
 * @param text            ��������� �� ��������� TextAnalyzer.
 * @param folderPath      ������ - ���� � ���������� � �������.
 * @param maximumWordSize ������������ ����� �����, ����� ������� ����� ������������.
*/
void TextParseIntoWordsDirectory(TextAnalyzer* text, const char* folderPath, const size_t maximumWordSize);

/**
 * @brief ��������� ���������� ���� � ������.
 *
 * @param text          ��������� �� ��������� TextAnalyzer.
 * @param maxWordLength ������������ ����� �����, ����� ������� ����� ������������.
 *
 * @return ���������� ���� � ������.
*/
size_t TextCountWords(const TextAnalyzer* text, const size_t maxWordLength);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif