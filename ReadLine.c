// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
#include <conio.h>
char* ReadLine(FILE* stream, bool_t* notEnd,error_t* error) {
	int i = 1;
	char *string = NULL;
	char *temp = NULL;
	char c = 0;
	bool_t errorMem = FALSE;
  while (c != '\n' && c != -1) {
    c = (char)getc(stream);
    temp = (char*)realloc(string, i);
    //temp = 0;
    if (temp != NULL) {
      string = temp;
      if (c == -1) {
        *notEnd = FALSE;
        string[i - 1] = 0;
        return string;
      }
      string[i - 1] = c;
    }
    else {
      if (c == -1) {
        *notEnd = FALSE;
      }
      errorMem = TRUE;
    }
    i++;
  }
	if (errorMem) {
		*error = ERROR_MEM;
    free(string);
		return 0;
	}
  string[i - 2] = 0;
	return string;
}
void ErrorDef(error_t ERROR) {
  char Errors[][51] = { {"ERROR: not enough memory"},
                        {"ERROR: sqrt for negative number"},
                        {"ERROR:file does not exist"},
                        {"ERROR: brackets"},
                        {"ERROR: exponential notation"},
                        {"ERROR: unknown operation"},
                        {"ERROR: definition error"},
                        {"ERROR: not enough operands"},
                        {"ERROR: wrong expression"},
                        {"ERROR: wrong variable"},
                        {"ERROR: 'e' can not be used for the variable's name"} };
	printf("%s\n", Errors[ERROR - 1]);
}
void PrintResult(char* string, error_t error, double result,scenaries_t scenary) {
	printf("%s", string);
  if (scenary) {
    printf(" == ");
  }
  else {
    printf("\n");
  }
  if (error) {
    ErrorDef(error);
  }
  else {
    if (scenary) {
      printf("%g\n", result);
    }
  }
}
int main(int argc, char* argv[]) {
	FILE *stream;
	char* string;
	double result;
	bool_t notEnd = TRUE;
	scenaries_t scenary = PRINT_ONLY_STRING;
	error_t error=ERROR_OK;
  if(argc > 2){
    error=ERROR_FILE;
    ErrorDef(error);
    return 0;
  }
  if (argc == 2) {
    fopen_s(&stream, argv[1], "r");
  }
  else {
    stream = stdin;
  }
  if (stream == NULL) {
    error = ERROR_FILE;
  }
	while (notEnd&&stream) {
    string = ReadLine(stream, &notEnd, &error);
		if (error) {
      if (notEnd != FALSE) {
        ErrorDef(error);
      }
			error = ERROR_OK;
			continue;
		}
		result = Processing(string, &error, &scenary);
    if (notEnd || string[0] != 0) {
      PrintResult(string, error, result, scenary);
    }
		scenary = PRINT_ONLY_STRING;
		free(string);
    error = ERROR_OK;
	}
  if (error) {
    ErrorDef(error);
  }
  if (stream) {
    fclose(stream);
  }
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
  _CrtDumpMemoryLeaks();
	return 0;
}