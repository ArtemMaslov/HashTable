#include <stdio.h>
#include <Windows.h>

#include "HashTable/HashTable_UnitTests.h"

#include "Logs/Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	LogsConstructor();

	//TestHashTable_Sheakspear();

	//TestHashTable_OptimizationFind();

	TestHashTable_OptimizationInsertRemove();

	LogsDestructor();
}

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\