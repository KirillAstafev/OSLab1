#include <Windows.h>
#include <wchar.h>
#include <stdio.h>
#include <string>

using namespace std;

void WriteToCurrentPosition(HANDLE hFile, string result);

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hIn, hOut;
	int lineCount;
	int* lineNumbers;
	char *inputFileName, *outputFileName;

	if (argc != 7) {
		printf_s("ньхайю! ббедемн мебепмне йнк-бн юпцслемрнб!\n");
		return 1;
	}

	lineCount = atoi(argv[1]);
	lineNumbers = (int *)malloc(sizeof(int) * lineCount);

	for (int i = 0; i < 3; i++)
		lineNumbers[i] = atoi(argv[i + 2]);

	inputFileName = argv[5];
	outputFileName = argv[6];

	hIn = CreateFileA(inputFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	hOut = CreateFileA(outputFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	char currentByte;
	int currentLineNumber = 1;
	DWORD numberOfBytes;
	string result;

	while (ReadFile(hIn, &currentByte, 1, &numberOfBytes, NULL) > 0 && numberOfBytes > 0) {
		for (int i = 0; i < 3; i++) {
			if (lineNumbers[i] == currentLineNumber) {
				result += currentByte;
				break;
			}
		}

		if (currentByte == 10) {
			currentLineNumber++;

			if (result.size()) {
				WriteToCurrentPosition(hOut, result);
				result.clear();
			}
		}
	}

	CloseHandle(hIn);
	CloseHandle(hOut);

	free(lineNumbers);
	return 0;
}

void WriteToCurrentPosition(HANDLE hFile, string result) {
	DWORD currentPos = SetFilePointer(hFile, 0, 0, FILE_CURRENT);
	int currentBufferPos = 0;

	string buff = result;

	char currentByte;
	DWORD numberOfBytes;

	while (ReadFile(hFile, &currentByte, 1, &numberOfBytes, NULL) > 0 && numberOfBytes > 0) {
		SetFilePointer(hFile, -1, NULL, FILE_CURRENT);

		WriteFile(hFile, &(buff[currentBufferPos]), 1, NULL, NULL);
		buff[currentBufferPos] = currentByte;

		if (++currentBufferPos == result.size())
			currentBufferPos = 0;
	}

	int endOfFilePos = currentBufferPos;
	
	for (int i = endOfFilePos; i < result.size(); i++)
		WriteFile(hFile, &(buff[i]), 1, NULL, NULL);
	for (int i = 0; i < endOfFilePos; i++)
		WriteFile(hFile, &(buff[i]), 1, NULL, NULL);

	SetFilePointer(hFile, currentPos + result.size(), NULL, FILE_BEGIN);
}