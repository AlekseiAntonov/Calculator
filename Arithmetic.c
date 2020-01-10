// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Header.h"
error_t CheckRes(double res) {
  double x = 0;
  if (res == (double)(1 / x) || res == -(double)(1 / x) || res != res) {
    return ERROR_DOMAIN;
  }
  return ERROR_OK;
}
bool_t BinaryOrNot(char symbol){
  bool_t x;
  switch (symbol) {
  case('+'):
  case('-'):
  case('*'):
  case('/'):
  case('^'):
  case(LOG): {
    x = TRUE;
    break;
  }
  default: {
    x = FALSE;
    break;
  }
  }
  return x;
}
result_t Calculating(result_t result, char symbol, error_t* error) {
  if (BinaryOrNot(symbol)) {
    if ((result.lastelem - 1) < 0) {
      *error = ERROR_OPERANDS_NUMBER;
      return result;
    }
  }
  else {
    if (result.lastelem < 0) {
      *error = ERROR_OPERANDS_NUMBER;
      return result;
    }
  }
  switch (symbol) {
  case('+'): {
    result.result[result.lastelem - 1] += result.result[result.lastelem];
    result.lastelem--;
    break;
  }
  case('-'): {
    result.result[result.lastelem - 1] -= result.result[result.lastelem];
    result.lastelem--;
    break;
  }
  case('*'): {
    if ((result.lastelem - 1) < 0) {
      *error = ERROR_OPERANDS_NUMBER;
      break;
    }
    result.result[result.lastelem - 1] *= result.result[result.lastelem];
    result.lastelem--;
    break;
  }
  case('/'): {
    result.result[result.lastelem - 1] /= result.result[result.lastelem];
    *error = CheckRes(result.result[result.lastelem - 1]);
    result.lastelem--;
    break;
  }
  case('^'): {
    result.result[result.lastelem - 1] = pow(result.result[result.lastelem - 1], result.result[result.lastelem]);
    *error = CheckRes(result.result[result.lastelem - 1]);
    result.lastelem--;
    break;
  }
  case(COS): {
    if (floor(result.result[result.lastelem] / (PI / 2)) == result.result[result.lastelem] / (PI / 2) && \
      floor(result.result[result.lastelem] / PI) != result.result[result.lastelem] / PI) {
      result.result[result.lastelem] = 0;
      break;
    }
    result.result[result.lastelem] = cos(result.result[result.lastelem]);
    break;
  }
  case(SIN): {
    if (floor(result.result[result.lastelem] / PI) == result.result[result.lastelem] / PI) {
      result.result[result.lastelem] = 0;
      break;
    }
    result.result[result.lastelem] = sin(result.result[result.lastelem]);
    break;
  }
  case(TG): {
    if (floor(result.result[result.lastelem] / PI) == result.result[result.lastelem] / PI) {
      result.result[result.lastelem] = 0;
      break;
    }
    if (floor(result.result[result.lastelem] / (PI / 2)) == result.result[result.lastelem] / (PI / 2) && result.result[result.lastelem] != 0) {
      *error = ERROR_DOMAIN;
      break;
    }
    result.result[result.lastelem] = tan(result.result[result.lastelem]);
    break;
  }
  case(CTG): {
    if (floor(result.result[result.lastelem] / (PI / 2)) == result.result[result.lastelem] / (PI / 2) && \
      floor(result.result[result.lastelem] / PI) != result.result[result.lastelem] / PI) {
      result.result[result.lastelem] = 0;
      break;
    }
    if (floor(result.result[result.lastelem] / PI) == result.result[result.lastelem] / PI) {
      *error = ERROR_DOMAIN;
      break;
    }
    result.result[result.lastelem] = 1 / tan(result.result[result.lastelem]);
    break;
  }
  case(SQRT): {
    result.result[result.lastelem] = sqrt(result.result[result.lastelem]);
    *error = CheckRes(result.result[result.lastelem]);
    break;
  }
  case(ARCSIN): {
    if (result.result[result.lastelem] > 1 || result.result[result.lastelem] < -1) {
      *error = ERROR_DOMAIN;
      break;
    }
    result.result[result.lastelem] = asin(result.result[result.lastelem]);
    break;
  }
  case(ARCCOS): {
    if (result.result[result.lastelem] > 1 || result.result[result.lastelem] < -1) {
      *error = ERROR_DOMAIN;
      break;
    }
    result.result[result.lastelem] = acos(result.result[result.lastelem]);
    break;
  }
  case(ARCTG): {
    result.result[result.lastelem] = atan(result.result[result.lastelem]);
    break;
  }
  case(LN): {
    result.result[result.lastelem] = log(result.result[result.lastelem]);
    *error = CheckRes(result.result[result.lastelem]);
    break;
  }
  case(FLOOR): {
    result.result[result.lastelem] = floor(result.result[result.lastelem]);
    break;
  }
  case(CEIL): {
    result.result[result.lastelem] = ceil(result.result[result.lastelem]);
    break;
  }
  case(UNARY_MIN): {
    result.result[result.lastelem] = result.result[result.lastelem] * (-1);
    break;
  }
  case(LOG): {
    result.result[result.lastelem - 1] = log(result.result[result.lastelem]) / log(result.result[result.lastelem - 1]);
    *error = CheckRes(result.result[result.lastelem - 1]);
    result.lastelem--;
    break;
  }
  default: {
    //—юда никогда не заходит
    break;
  }
  }
  return result;
}