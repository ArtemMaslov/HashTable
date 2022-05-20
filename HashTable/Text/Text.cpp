#include <assert.h>
#include <stdlib.h>

#include "..\Logs\Logs.h"
#include "..\FileIO.h"

#include "Text.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int TextConstructor(Text* text, const size_t wordsCapacity)
{
	assert(text);

	text->RawDataSize   = 0;
	text->RawData       = nullptr;

	text->Status        = TEXT_ERR_NO_ERRORS;

	text->WordsSize     = 0;
	text->WordsCapacity = wordsCapacity;
	text->Words         = (Word*)calloc(wordsCapacity, sizeof(Word));

	if (!text->Words)
	{
		LOG_ERR_MEMORY;

		text->Status |= TEXT_ERR_MEMORY;

		return text->Status;
	}

	return text->Status;
}

void TextDestructor(Text* text)
{
	assert(text);

	text->WordsCapacity = 0;
	text->WordsSize     = 0;

	text->Status        = TEXT_ERR_NO_ERRORS;

	TextClearRawData(text);

	free(text->Words);
}

void TextClearRawData(Text* text)
{
	assert(text);

	free(text->RawData);

	text->RawData     = nullptr;
	text->RawDataSize = 0;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

void TextReadFile(Text* text, const char* fileName)
{
	assert(text);
	assert(fileName);

	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		LOG_F_ERR("Ошибка открытия файла \"%s\"", fileName);
		text->Status = TEXT_ERR_FILE;
		return;
	}

	const size_t fileSize = GetFileSize(file);

	char* buffer = (char*)calloc(fileSize + 1, sizeof(char));

	if (!buffer)
	{
		LOG_ERR("Ошибка выделения памяти.");
		text->Status = TEXT_ERR_MEMORY;
		return ;
	}

	size_t readed = fread(buffer, sizeof(char), fileSize, file);

	fclose(file);

	text->Status = TEXT_ERR_NO_ERRORS;

	text->RawData     = buffer;
	text->RawDataSize = fileSize;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\