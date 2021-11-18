#include <Windows.h>
#include <wchar.h>
#include <stdio.h>
#include <string>

#define ROW_COUNT 4

using namespace std;

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hIn, hOut;
	int lineCount;
	int lineNumbers[ROW_COUNT];
	char *inputFileName, *outputFileName;

	if (argc != 8) {
		printf_s("ньхайю! ббедемн мебепмне йнк-бн юпцслемрнб!\n");
		return 1;
	}

	lineCount = atoi(argv[1]);

	for (int i = 0; i < ROW_COUNT; i++)
		lineNumbers[i] = atoi(argv[i + 2]);

	inputFileName = argv[6];
	outputFileName = argv[7];

	hIn = CreateFileA(inputFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	hOut = CreateFileA(outputFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	SetFilePointer(hOut, 0, NULL, FILE_END);

	char currentByte;
	int currentLineNumber = 1;
	DWORD numberOfBytes;
	string result;

	while (ReadFile(hIn, &currentByte, 1, &numberOfBytes, NULL) > 0 && numberOfBytes > 0) {
		for (int i = 0; i < ROW_COUNT; i++) {
			if (lineNumbers[i] == currentLineNumber) {
				result += currentByte;
				break;
			}
		}

		if (currentByte == 10) {
			currentLineNumber++;

			if (result.size()) {
				printf_s("гюохяэ ярпнйх: ");
				puts(result.c_str());

				WriteFile(hOut, result.c_str(), result.size(), NULL, NULL);
				result.clear();
			}
		}
	}

	BOOL res = SetFileAttributesA(outputFileName, FILE_ATTRIBUTE_ENCRYPTED | FILE_ATTRIBUTE_ARCHIVE);

	CloseHandle(hIn);
	CloseHandle(hOut);

	printf_s("ярпнйх сяоеьмн яйнохпнбюмш\n");

	system("pause");
	return 0;
}