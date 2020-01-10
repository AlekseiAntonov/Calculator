// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef Header_H
#define Header_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <crtdbg.h> 
#include <math.h>
#define COS 'o'
#define SIN 's'
#define TG 't'
#define CTG 'c'
#define SQRT 'q'
#define ARCSIN 'a'
#define ARCCOS 'r'
#define ARCTG 'g'
#define LN 'n'
#define FLOOR 'f'
#define CEIL 'e'
#define UNARY_MIN 'm'
#define LOG 'l'
#define PI 3.1415926535897932384626433832795
#define E 2.7182818284590452353602874713527
typedef enum {
  FALSE,
  TRUE,
}bool_t;
typedef enum {
  NORMAL_MODE,
  VARIABLE_MODE,
}modes_t;
typedef enum {
	PLUS,
	MINUS,
	MULTIPLY,
	DEVISION,
	DEGREE,
	COS_n,
	SIN_n,
	TG_n,
	CTG_n,
	SQRT_n,
	ARCSIN_n,
	ARCCOS_n,
	ARCTG_n,
	LN_n,
	FLOOR_n,
	CEIL_n,
  LOG_n,
	LAST_ELEM,
}functions_t;
typedef enum {
  NEUTRAL,
  NUMBER,
  OPERATION,
  FUNCTION,
  BRACKET_OPEN,
  BRACKET_CLOSE,
}operand_t;
typedef enum {
  ERROR_OK,
  ERROR_MEM,
  ERROR_MINSQRT,
  ERROR_FILE,
  ERROR_BRACK,
  ERROR_EXP,
  ERROR_OPERATIONS,
  ERROR_DOMAIN,
  ERROR_OPERANDS_NUMBER,
  ERROR_WRONG_EXPRESSION,
  ERROR_WRONG_VARIABLE,
  ERROR_CONST_AS_A_VARIABLE,
	ERROR_LAST
}error_t;
typedef enum {
  PRINT_ONLY_STRING,
  PRINT_RESULT,
}scenaries_t;
typedef struct
{
	char* stack;
	int size;
	int lastelem;
}stack_t;
typedef struct
{
	double* result;
	int size;
	int lastelem;
}result_t;
typedef struct {
	const char* functions;
	const int length[LAST_ELEM];
}funcs_t;
typedef struct {
  char* variables;
  double* values;
  int size;
}variables_t;
void ErrorDef(error_t ERROR);
funcs_t CreateFun(void);
int DefinePriority(char symbol);
result_t Calculating(result_t result, char symbol,error_t* error);
void AddToStack(result_t* result, stack_t* stack, char operation,error_t* error,operand_t previos);
result_t AddToRes(result_t result, double x, error_t* error);
double DefineNumber(char* string, int* position, error_t* error, variables_t* variables);
char OperationDefinition(const char* string, int* position, const funcs_t* functions, error_t* error, operand_t* previos);
double MainProcess(char* string, error_t* error);
char* ReadLine(FILE* stream, bool_t* notEnd, error_t* error);
bool_t BracErr(const char* string, int length);
bool_t EmptyStr(const char* string, int length);
double Processing(char* string, error_t* error, scenaries_t* scenary);
void PrintResult(char* string, error_t error, double result, scenaries_t scenary);
error_t CheckRes(double res);
bool_t Condition(const stack_t* stack, int stackPriority, int operPriority, char operation);
operand_t TypeDefinition(char symbol);
modes_t VariableDef(const char* string, int* position, char symbol, variables_t* variables, error_t* error);
double Peek(const variables_t* variable, char symbol, error_t* error);
void Push(variables_t* variables, char symbol, error_t* error);
bool_t CheckRus(const char* string, int length);
void GetLastError(modes_t mode, operand_t operType, bool_t waitForNum, error_t* error);
void EndOfVariableInicialisation(modes_t* mode, stack_t* stack, result_t* result, operand_t* operType, variables_t* variables, error_t* error);
#endif