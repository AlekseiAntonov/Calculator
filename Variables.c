// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
//Function VariableDef define if the position is a start of variable inicialisation
modes_t VariableDef(const char* string, int* position, char symbol, variables_t* variables, error_t* error) {
  int tempPosition = *position + 1;
  *position += 1;
  while (string[tempPosition] != '=') {
    if (!isspace(string[tempPosition])) {
      return NORMAL_MODE;
    }
    tempPosition += 1;
  }
  if (symbol == 'e') {
    *error = ERROR_CONST_AS_A_VARIABLE;
  }
  *position = tempPosition;
  Push(variables, symbol, error);
  return VARIABLE_MODE;
}
//Function Push add a symbol on the stack's top or an error in case of lack of memory
void Push(variables_t* variables, char symbol, error_t* error) {
  int i;
  double* tempD=NULL;
  char* tempC = NULL;
  for (i = 0; i < variables->size; i++) {
    if (symbol == variables->variables[i]) {
      return;
    }
  }
  variables->size++;
  tempD = (double*)realloc(variables->values, variables->size*sizeof(double));
  //variables->values = NULL;
  if (tempD == NULL) {
    free(variables->values);
    variables->values = NULL;
    *error = ERROR_MEM;
    return;
  }
  variables->values = tempD;
  tempC = (char*)realloc(variables->variables, variables->size);
  if (tempC == NULL) {
    free(variables->variables);
    variables->variables = NULL;
    *error = ERROR_MEM;
    return;
  }
  variables->variables = tempC;
  variables->variables[variables->size - 1] = symbol;
}
//Function Peek returns the value of variable, or an error
double Peek(const variables_t* variable, char symbol, error_t* error) {
  int i;
  for (i = 0; i < variable->size; i++) {
    if (variable->variables[i] == symbol) {
      return variable->values[i];
    }
  }
  *error = ERROR_WRONG_VARIABLE;
  return 0;
}