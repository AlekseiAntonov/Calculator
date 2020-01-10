// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
operand_t TypeDefinition(char symbol) {
  switch (symbol)
  {
  case ('+'):
  case ('-'):
  case ('*'):
  case ('/'):
  case ('^'):
  case (UNARY_MIN): {
    return OPERATION;
    break;
  }
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
    return FUNCTION;
    break;
  }
  default: {
    return 0;
    break;
  }
  }
}
bool_t Condition(const stack_t* stack, int stackPriority, int operPriority, char operation) {
  int j = 0;
  if (stack->lastelem >= 0) {
    j++;
  }
  if (stackPriority >= operPriority) {
    j++;
  }
  if (operation != '(') {
    j++;
  }
  if ((operPriority + stackPriority) != 14) {
    j++;
  }
  if (operation == '^' && (stack->lastelem >= 0 && TypeDefinition(stack->stack[stack->lastelem]) == FUNCTION)) {
    j++;
  }
   return j == 4;
}
void AddToStack(result_t* result, stack_t* stack, char operation, error_t* error,int previos) {
	char* temp = NULL;
  int operPriority = DefinePriority(operation);
  int stackPriority=0;
  previos = 4;
  if (stack->lastelem >= 0) {
    stackPriority = DefinePriority(stack->stack[stack->lastelem]);
  }
	while (Condition(stack,stackPriority,operPriority,operation) ){
		*result = Calculating(*result, stack->stack[stack->lastelem],error);
    if (!error) {
      return;
    }
    if (--stack->lastelem >= 0) {
      stackPriority = DefinePriority(stack->stack[stack->lastelem]);
    }
	}
	stack->lastelem++;
	if (stack->lastelem >= stack->size) {
		stack->size++;
		temp = (char*)realloc(stack->stack, stack->size);
    if (temp != NULL) {
      stack->stack = temp;
    }
		else {
		  *error = ERROR_MEM;
			return;
		}
	}
	stack->stack[stack->lastelem] = operation;
}
result_t AddToRes(result_t result, double x, error_t* error) {
	double* tmp = NULL;
	int pos;
	if ((result.lastelem + 1) == result.size) {
		result.size++;
		tmp = (double*)realloc(result.result, result.size * sizeof(double));
		if (tmp != NULL) {
			result.result = tmp;
    }
    else {
      *error = ERROR_MEM;
      return result;
    }
	}
	result.lastelem++;
	pos = result.lastelem;
	result.result[pos] = x;
	return result;
}