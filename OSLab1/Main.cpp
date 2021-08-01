#include <Windows.h>
#include <wchar.h>
#include <stdio.h>

int _tmain(int argc, wchar_t* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hIn, hOut;
	int lineCount;
	int* lineNumbers;
	wchar_t *inputFileName, *outputFileName;

	if (argc != 7) {
		printf_s("ньхайю! ббедемн мебепмне йнк-бн юпцслемрнб!\n");
		return 1;
	}

	lineCount = _wtoi(argv[1]);
	lineNumbers = (int *)malloc(sizeof(int) * lineCount);

	for (int i = 0; i < 3; i++)
		lineNumbers[i] = _wtoi(argv[i + 2]);

	inputFileName = argv[5];
	outputFileName = argv[6];

	hIn = CreateFile(inputFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	hOut = CreateFile(outputFileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	char currentByte;
	int currentLineNumber;

	free(lineNumbers);
	return 0;
}