// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
double Processing(char* string,error_t* error,scenaries_t* scenary) {
	int length = strlen(string);
	double result;
  if (*string == 0) {
    return 1;
  }
	if (BracErr(string, length)) {
		*error = ERROR_BRACK;
		*scenary = PRINT_RESULT;
		return 1;
	};
	if (EmptyStr(string, length)) {
		*scenary = PRINT_ONLY_STRING;
		return 1;
	};
  if (CheckRus(string, length)) {
    *error = ERROR_WRONG_EXPRESSION;
    *scenary = PRINT_RESULT;
    return 1;
  }
	result = MainProcess(string,error);
	*scenary = PRINT_RESULT;
	return result;
}
bool_t EmptyStr(const char* string, int length) {
	int i;
	for (i = 0; i < length; i++) {
    if (string[i] < 0) {
      return FALSE;
    }
		if (!isspace(string[i])) {
      if (string[i] == '/' && string[i + 1] == '/') {
        return TRUE;
      }
      else {
        return FALSE;
      }
		};
	};
	return TRUE;
}
bool_t BracErr(const char* string, int length) {
	int i;
	int k = 0;
	for (i = 0; i < length && k >= 0; i++) {
    if (string[i] == '(') {
      k++;
    }
    if (string[i] == ')') {
      k--;
    }
	}
		return k!=0;
}
bool_t CheckRus(const char* string, int length) {
  int i;
  for (i = 0; i < length; i++){
    if (string[i] < 0) {
      return TRUE;
    }
  }
  return FALSE;
}