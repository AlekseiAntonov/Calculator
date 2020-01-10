// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
double MainProcess(char* string, error_t* error) {
	int length = strlen(string);
	int i;
	char op = 0;
	double resultX = 0;
  bool_t waitForNum = FALSE;
  operand_t operType = NEUTRAL;
  modes_t mode = NORMAL_MODE;
  modes_t tempMode = NORMAL_MODE;
	funcs_t functions = CreateFun();
	stack_t stack = {{0}, {0}, {-1}};
	result_t result = {{0}, {0}, {-1}};
  variables_t variables = {{0}, {0}, {0}};
	for (i = 0; i < length && *error == ERROR_OK; i++){
    if (isspace(string[i])) {
      continue;
    }
    if (isalpha(string[i])) {
      tempMode = VariableDef(string, &i, string[i], &variables, error);
      if (*error != ERROR_OK) {
        continue;
      }
      if (tempMode == VARIABLE_MODE && mode == VARIABLE_MODE) {
        *error = ERROR_WRONG_VARIABLE;
      }
      if (tempMode == VARIABLE_MODE) {
        mode = tempMode;
        continue;
      }
      if (string[i] != '=') {
        i--;
      }
    }
    if (isspace(string[i])) {
      continue;
    }
		if (isdigit(string[i]) || string[i] == 'p'||string[i] == 'e'||string[i]=='.'){
      if (operType == NUMBER || operType == BRACKET_CLOSE||(stack.lastelem>=0 && stack.stack[stack.lastelem]==LOG)) {
        *error = ERROR_WRONG_EXPRESSION;
        break;
      }
      operType = NUMBER;
      waitForNum = FALSE;
      resultX = DefineNumber(string, &i, error, &variables);
      if (*error != ERROR_OK) {
        break;
      }
			result = AddToRes(result, resultX, error);
			continue;
		}
		op = OperationDefinition(string, &i, &functions, error, &operType);
		if (*error != ERROR_OK) {
      if (*error == ERROR_OPERATIONS) {
        if (string[i] == ',') {
          *error = ERROR_OK; 
          while (stack.lastelem>=0 && stack.stack[stack.lastelem] != '(') {
            result = Calculating(result, stack.stack[stack.lastelem--], error);
            if (*error != ERROR_OK) {
              free(result.result);
              free(stack.stack);
              return 0;
            }
          }
          if (stack.lastelem - 1 < 0 || stack.stack[stack.lastelem - 1] != LOG) {
            *error = ERROR_OPERATIONS;
          }
          operType = BRACKET_OPEN;
          continue;
        }
        if (string[i] == ';') {
          EndOfVariableInicialisation(&mode, &stack, &result, &operType, &variables, error);
          /*if (mode == VARIABLE_MODE) {
            mode = NORMAL_MODE;
            *error = ERROR_OK;
            while (stack.lastelem >= 0 && *error == ERROR_OK) {
              result = Calculating(result, stack.stack[stack.lastelem--], error);
            }
            if (result.result) {
              variables.values[variables.size - 1] = result.result[0];
            }
            if (result.lastelem != 0) {
              *error = ERROR_OPERANDS_NUMBER;
            }
            operType = NEUTRAL;
            stack.lastelem = -1;
            result.lastelem = -1;
            if (*error != ERROR_OK) {
                free(variables.values);
                free(variables.variables);
                free(stack.stack);
                free(result.result);
              return 0;
            }
          }*/
          if (*error != ERROR_OK) {
            free(variables.values);
            free(variables.variables);
            free(stack.stack);
            free(result.result);
            return 0;
          }
          continue;
        }
        *error = ERROR_OK;
        resultX = Peek(&variables, string[i], error);
        operType = NUMBER;
        result = AddToRes(result, resultX, error);
        waitForNum = FALSE;
        continue;
      }
      continue;
		}
		if (op && op != ')'){
      if (stack.lastelem >= 0 && stack.stack[stack.lastelem] == LOG && op!='(') {
        *error = ERROR_WRONG_EXPRESSION;
        continue;
      }
			AddToStack(&result, &stack, op, error,operType);
      if (*error != ERROR_OK) {
        break;
      }
      if (TypeDefinition(op) == OPERATION || TypeDefinition(op) == FUNCTION) {
        waitForNum = TRUE;
      }
			op = 0;
      continue;
		}
    if (string[i] == ')') {
      while (stack.stack[stack.lastelem] != '(') {
        result = Calculating(result, stack.stack[stack.lastelem--], error);
        if (*error != ERROR_OK) {
          free(result.result);
          free(stack.stack);
          return 0;
        }
      }
      stack.lastelem--;
      if (stack.lastelem >= 0 && stack.stack[stack.lastelem] == LOG) {
        result = Calculating(result, stack.stack[stack.lastelem--], error);
      }
    }
	}
  GetLastError(mode, operType, waitForNum, error);
  while (stack.lastelem >= 0 && *error == ERROR_OK) {
    result = Calculating(result, stack.stack[stack.lastelem--], error);
  }
  if (*error != ERROR_OK) {
    free(result.result);
    free(stack.stack);
    free(variables.values);
    free(variables.variables);
    return 0;
  }
  if (result.result) {
    resultX = result.result[0];
  }
  if (result.lastelem != 0) {
    *error = ERROR_OPERANDS_NUMBER;
  }
  free(variables.values);
  free(variables.variables);
	free(result.result);
	free(stack.stack);
	return resultX;
}
void GetLastError(modes_t mode, operand_t operType, bool_t waitForNum,error_t* error) {
  if (mode == VARIABLE_MODE) {
    *error = ERROR_WRONG_VARIABLE;
    return;
  }
  if ((operType == OPERATION || operType == FUNCTION || waitForNum) && *error == ERROR_OK) {
    *error = ERROR_WRONG_EXPRESSION;
    return;
  }
  return;
}
void EndOfVariableInicialisation(modes_t* mode, stack_t* stack, result_t* result, operand_t* operType, variables_t* variables, error_t* error) {
  if (*mode == VARIABLE_MODE) {
    *mode = NORMAL_MODE;
    *error = ERROR_OK;
    while (stack->lastelem >= 0 && *error == ERROR_OK) {
      *result = Calculating(*result, stack->stack[stack->lastelem--], error);
    }
    if (result->result) {
      variables->values[variables->size - 1] = result->result[0];
    }
    if (result->lastelem != 0) {
      *error = ERROR_OPERANDS_NUMBER;
    }
    *operType = NEUTRAL;
    stack->lastelem = -1;
    result->lastelem = -1;
  }
}