// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
//Function DefineNumber define the number and constants starting from the position
double DefineNumber(char* string, int* position, error_t* error, variables_t* variables) {
	double result = 0;
	int i = 0;
	int j;
	int k = 1;
	double tempCategory = 0;
	double category = 0.1;
	char* location = string + *position;
  if (string[*position] == 'e') {
    return E;
  }
  if (string[*position] == 'p') {
    if (string[*position + 1] == 'i') {
      *position += 1;
      return PI;
    }
    else {
      return Peek(variables, 'p', error);
    }
  }
  while (isdigit(*(location + i))) {
    i++;
  }
	*position += i - 1;
	if (string[*position + 1] == '.'||string[*position]=='.') {
		*position += 1;
		while (isdigit(string[*position + 1])) {
			result += category * (string[*position + 1] - 48);
			*position += 1;
			category *= 0.1;
		}
	}
	category = 1;
	for (; i > 0; i--) {
		result += category * ((*(location + i - 1)) - 48);
		category *= 10;
	};
	category = 1;
	i = 0;
	if (string[*position + 1] == 'e' || string[*position + 1] == 'E') {
		*position += 1;
		if (!isdigit(string[*position + 1]) && (string[*position + 1] != '+' && string[*position + 1] != '-')) {
			*error = ERROR_EXP;
			return 0;
		}
		if (string[*position + 1] == '-') {
			k = -1;
			*position += 1;
			if (!isdigit(string[*position + 1])) {
				*error = ERROR_EXP;
				return 0;
			}
		}
		if (string[*position + 1] == '+') {
			*position += 1;
			if (!isdigit(string[*position + 1])) {
				*error = ERROR_EXP;
				return 0;
			}
		}
    while (isdigit(string[*position + 1 + i])) {
      i++;
    }
		*position += i;
		for (j = 0; j < i; j++) {
			tempCategory += (string[*position - j]-48) * category;
			category *= 10;
		}
	}

	return result * pow(10,k*tempCategory);
}
// Function CreateFun creates the structure of names of operations and their lenghts
funcs_t CreateFun(void) {
	funcs_t functions = { "+-*/^cossintgctgsqrtarcsinarccosarctglnfloorceillog",1,1,1,1,1,3,3,2,3,4,6,6,5,2,5,4,3 };
	return functions;
}
//Function OperationDefinition returns the symbol of operation used
char OperationDefinition(const char* string, int* position, const funcs_t* functions,error_t* error, operand_t* previos) {
	functions_t i;
	int tmp = 0;
	char oper[] = { '+', '-', '*', '/', '^', COS, SIN, TG, CTG, SQRT, ARCSIN, ARCCOS, ARCTG, LN, FLOOR, CEIL, LOG };
  if (string[*position] == '(') {
    *previos = BRACKET_OPEN;
    return '(';
  }
  if (string[*position] == ')') {
    if (*previos == BRACKET_OPEN) {
      *error = ERROR_BRACK;
    }
    *previos = BRACKET_CLOSE;
    return ')';
  }
	for (i = PLUS; i < LAST_ELEM; i++) {
		if (!memcmp(string + *position, functions->functions + tmp, functions->length[i])) {
      if (oper[i] == '-' && *previos != NUMBER && *previos!=BRACKET_CLOSE) {
        *previos = FUNCTION;
        return UNARY_MIN;
      }
      if (i < COS_n) {
        if (*previos == OPERATION || *previos == FUNCTION) {
          *error = ERROR_WRONG_EXPRESSION;
        }
        else {
          *previos = OPERATION;
        }
      }
      if (i >= COS_n) {
        *previos = FUNCTION;
      }
      *position += functions->length[i] - 1;
      return oper[i];
		}
    else {
      tmp += functions->length[i];
    }
	}
	*error = ERROR_OPERATIONS;
	return 0;
}
//Function DefinePriority return the priority level of operation
int DefinePriority(char symbol){
  int priority=0;
	switch (symbol) {
	case('+'):
  case('-'): {
    priority = 1;
    break;
  }
	case('/'):
  case('*'): {
    priority = 2;
    break;
  }
  case(UNARY_MIN):
	case('^'):
	case(COS):
	case(SIN):
	case(TG):
	case(CTG):
	case(SQRT):
	case(ARCSIN):
	case(ARCCOS):
	case(ARCTG):
	case(LN):
	case(FLOOR):
	case(CEIL):
  case(LOG): {
    priority = 7;
    break;
  }
  default: {
    priority = -1;
    break;
  }
	}
	return priority;
}