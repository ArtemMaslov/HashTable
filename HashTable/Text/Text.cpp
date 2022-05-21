#include <assert.h>
#include <stdlib.h>

#include "..\Logs\Logs.h"
#include "..\FileIO.h"

#include "Text.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int TextConstructor(TextAnalyzer* text, const size_t wordsCapacity, const size_t textsCapacity)
{
	assert(text);
	assert(textsCapacity);
	
	text->Status        = TEXT_ERR_NO_ERRORS;

	text->TextsSize     = 0;
	text->TextsCount = textsCapacity;
	text->Texts         = (Text*)calloc(textsCapacity, sizeof(Text));

	if (!text->Texts)
	{
		LOG_ERR_MEMORY;

		text->Status |= TEXT_ERR_MEMORY;
		
		return text->Status;
	}
							    
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

void TextDestructor(TextAnalyzer* text)
{
	assert(text);

	const size_t textsCount = text->TextsCount;
	
	Text* texts = text->Texts;

	for (size_t st = 0; st < textsCount; st++)
	{
		free(texts[st].Data);

		texts[st].Size  = 0;
		texts[st].Data  = nullptr;
	}

	free(text->Texts);

	text->TextsCount    = 0;
	text->Texts         = nullptr;

	free(text->Words);

	text->WordsCapacity = 0;
	text->WordsSize     = 0;

	text->Status        = TEXT_ERR_NO_ERRORS;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int TextReadFile(TextAnalyzer* text, const char* fileName)
{
	assert(text);
	assert(fileName);

	const size_t textsSize = text->TextsSize;

	if (textsSize > text->TextsCount)
	{
		LOG_ERR("Попытка добавить текст в заполненную структуру TextAnalyzer.");

		text->Status = TEXT_ERR_OVERFLOW;

		return text->Status;
	}

	FILE* file = fopen(fileName, "r");

	if (!file)
	{
		LOG_F_ERR("Ошибка открытия файла \"%s\"", fileName);

		text->Status = TEXT_ERR_FILE;

		return text->Status;
	}

	const size_t fileSize = GetFileSize(file);

	char* buffer = (char*)calloc(fileSize + 1, sizeof(char));

	if (!buffer)
	{
		LOG_ERR("Ошибка выделения памяти.");

		text->Status = TEXT_ERR_MEMORY;

		return text->Status;
	}

	size_t readed = fread(buffer, sizeof(char), fileSize, file);

	fclose(file);

	text->Texts[textsSize].Data = buffer;
	text->Texts[textsSize].Size = fileSize;

	text->TextsSize++;

	return text->Status;
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\