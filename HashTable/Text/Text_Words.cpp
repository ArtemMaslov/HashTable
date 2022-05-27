#include <assert.h>
#include <stdlib.h>

#include <Windows.h>

#include "..\Logs\Logs.h"
#include "..\FileIO.h"

#include "Text.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#define IS_LETTER(letter) ((letter) >= 'a' && (letter) <= 'z' || (letter) >= 'A' && (letter) <= 'Z')

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/**
 * @brief Выделить дополнительную память для массива слов.
 * 
 * @param text        Указатель на структуру TextAnalyzer.
 * @param newCapacity Размер, который требуется выделить.
*/
static void TextAllocWords(TextAnalyzer* text, const size_t newCapacity);

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

void TextParseIntoWordsDirectory(TextAnalyzer* text, const char* folderPath, const size_t maximumWordSize)
{
	assert(text);
	assert(folderPath);

	WIN32_FIND_DATA fileData = {};

	HANDLE handle = FindFirstFile(folderPath, &fileData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		LOG_ERR("Не удаётся найти текстовые файлы в папке tests");

		text->Status |= TEXT_ERR_FILE;

		return;
	}

	char filePath[1024] = "";

	do
	{
		sprintf(filePath, "tests\\%s", fileData.cFileName);

		TextReadFile(text, filePath);

		if (text->Status != TEXT_ERR_NO_ERRORS)
			break;

	} while (FindNextFile(handle, &fileData));

	TextParseIntoWords(text, maximumWordSize);

	LOG_DBG("File parsed");

	FindClose(handle);
}

void TextParseIntoWords(TextAnalyzer* text, const size_t maxWordLength)
{
	assert(text);
	assert(text->Texts);

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	size_t  wordIndex   = text->WordsSize;
	bool    wordStarted = false;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\
	
	size_t newCapacity = TextCountWords(text, maxWordLength) + text->WordsSize;

	TextAllocWords(text, newCapacity);

	if (text->Status != TEXT_ERR_NO_ERRORS)
		return;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\
	
	const size_t textsCount = text->TextsSize;
	const Text*  texts      = text->Texts;
	      Word*  words      = text->Words;

	for (size_t st = 0; st < textsCount; st++)
	{
		size_t wordSize    = 0;
		bool   wordStarted = false;
		char*  wordStart   = nullptr;

		char*  data        = texts[st].Data;

		while (*data)
		{
			if (wordStarted == false)
			{
				if (IS_LETTER(*data))
				{
					wordStart   = data;
					wordSize    = 1;

					wordStarted = true;
				}
			}
			else
			{
				if (IS_LETTER(*data))
				{
					wordSize++;
				}
				else
				{
					if (wordSize <= maxWordLength)
					{
						words[wordIndex].Data = wordStart;
						words[wordIndex].Size = wordSize;

						wordIndex++;
					}

					wordStarted = false;
				}
			}

			data++;
		}
	}

	text->WordsSize = wordIndex;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

size_t TextCountWords(const TextAnalyzer* text, const size_t maxWordLength)
{
	assert(text);

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	size_t wordsCount = 0;

	const size_t textsCount = text->TextsSize;
	const Text*  texts      = text->Texts;

	for (size_t st = 0; st < textsCount; st++)
	{
		size_t wordSize    = 0;
		bool   wordStarted = false;

		const char* data = texts[st].Data;

		//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

		while (*data)
		{
			if (wordStarted == false)
			{
				if (IS_LETTER(*data))
				{
					wordSize    = 1;
					wordStarted = true;
				}
			}
			else
			{
				if (!IS_LETTER(*data))
				{
					if (wordSize <= maxWordLength)
						wordsCount++;

					wordStarted = false;
				}
				else
					wordSize++;
			}

			data++;
		}
	}

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	return wordsCount;
}

static void TextAllocWords(TextAnalyzer* text, const size_t newCapacity)
{
	assert(text);

	if (newCapacity < text->WordsCapacity)
		return;

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	Word* ptr = (Word*)realloc(text->Words, sizeof(Word) * newCapacity);

	if (!ptr)
	{
		LOG_ERR_MEMORY;

		text->Status |= TEXT_ERR_MEMORY;

		return;
	}

	//***\\---//***\\-----//***\\---//***\\-----//*****\\-----//***\\---//***\\-----//***\\---//***\\

	text->WordsCapacity = newCapacity;
	text->Words = ptr;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#undef IS_LETTER