# Calculator
The programe that calculates string expressions, supports brackets and handles errors


## 1. Form of programe.


**1.1. Programming language: ANSI C, 1989 standard, plus Microsoft add-ons (ex., crtdbg.h debugging);**

**1.2. Algorithm: conversion to inverse Polish notation with its calculation;**



## 2. Form of testing program.


**2.1. The program is a console application (Win32 Console Application);**

  2.1.1. If the program is run without parameters, the input data is read from the standard stream, line 
  by line, to the end of the stream;

  2.1.2. If the program is run with one parameter (file name), the input data is read from this text file, 
  line by line, to the end (stream);

  2.1.3. If the program is started without parameters, but with input and/or output redirection, it works 
  similarly to the previous two ways of starting;

  2.1.4. If the command-line options do not match the cases described, the program displays a single line 
  containing an error message - "ERROR: too many arguments";

  2.1.5. The output is displayed in the standard output. One line read corresponds to one printed, 
  completed line feed;

  2.1.6. Blank lines and comment lines are read displayed unchanged. An empty string is a string that 
  contains zero or more whitespace characters and is not located at the end of the file. A comment string 
  is a string that begins with two slashes “//” and contains arbitrary text. The string may contain 
  whitespace characters before the comment, but not other text;

  2.1.7. The remaining strings are taken as expressions and evaluated immediately. The original formula 
  is displayed unchanged and, in the same line, the numerical value of the result (or a brief description
  of the error). The original formula is separated from the result (or error) by a double equal sign (==),
  framed by spaces;

  2.1.8. The output format corresponds to the specifier "%g " (final zeros are not output, if necessary, 
  the scientific form of the record is used);

  2.1.9. If an error occurs during expression processing, the error message is displayed instead of the
  result (after the equal sign). It begins with the phrase " ERROR:" followed by a space-separated
  explanation of the problem. The work of the program is not interrupted;

  2.1.10. There is no explicit or implicit limit on the length of the input (and output) string. The
  program correctly reads and processes strings of any length;

**2.2. The principle of modularity is observed: the algorithm is logically and physically separated from
the user interface.**

2.2.1. The computational algorithm is designed as a separate function that takes as input a string in
which the expression is written (double Calculate(char * expression, type_errors_t* ERR));

2.2.2. This basic function does one thing-calculating an expression, and does not read anything from
the keyboard or display. It is divided into auxiliary subfunctions that perform separate subtasks;

2.2.3. This main and all auxiliary functions are placed in a separate module (s); have their own header file;

**2.3 Run-time errors are handled.**

2.3.1. The program is maximally protected from incorrect input data ("foolproof"), input / output errors, as
well as from errors that occur during calculations (such as division by zero);

2.3.2. The algorithmic module informs the interface module that an error has occurred;

2.3.3. Low memory cases are correctly handled like other run-time errors. If there is insufficient memory
during calculations, an error message is displayed instead of the result. If there is insufficient memory
while reading an input string, an error message (“ERROR: not enough memory”) is displayed instead of the
entire expression, and the input data is correctly skipped to the beginning of the next string (containing
the next expression). The program does not crash, the lack of memory for one expression does not mean that
it will not be enough for the rest.

**2.4. The program is tested by a special tool-Linter (PVS-Studio), which helps to detect a large number of
logical errors and inaccuracies. Most of the identified bugs and instabilities (potential bugs) have been
fixed, primarily at the High and Medium levels.**



## 3. The functionality of the counting module.


**3.1. Expressions are a set of operands separated by operation signs with corresponding precedence and
associativity known from mathematics and / or C and other languages. There is no explicit or implicit limit
on the complexity of the expression except for the lack of RAM. The algorithm correctly and quickly reads
and processes expressions of any complexity (as well as strings of any length).**

**3.2. The operands may be:**

3.2.1. Integers (constants);

3.2.2. Real numbers (literal constants), including in scientific (exponential) form;

3.2.3. The named constants pi and e are specified with sufficient (maximum possible) precision.

**3.3. Basic arithmetic operations are supported:**

3.3.1. Unary minus (−a). Does not require parentheses for correct calculation of several cons in a row,
because the order of calculations is determined uniquely: 1+---2 = -1;

3.3.2. Binary addition (a+b), subtraction (a−b), multiplication, division (a/b) and exponentiation (a^b).
In terms of priority, there is not immediately obvious behavior of the degree with respect to the unary
minus: -2^2 = -4;

3.3.3. Parentheses for grouping (overriding priority). Parentheses are not required in the case where the
order of application of operations is clear and unambiguously defined.

**3.4. In addition to operations, formulas can contain function calls of the form "sin(5)" (a kind of unary
operation). Brackets may or may not be present. The following features must be supported:**

3.4.1. root (sqrt);

3.4.2. trigonometric (sin, cos, tg, ctg, arcsin, arccos, arctg);

3.4.3. the natural logarithm (ln);

3.4.4. rounding down (floor) and up (ceil);

3.4.5. a logarithm function on an arbitrary basis “log(a, x)” from two arguments.

**3.5. Formulas can contain any whitespace characters that do not interfere with calculations (the free form
of the expression record), that is, do not break the lexeme into parts.**

**3.6. Storing intermediate results in temporary variables and using them as operands. This involves sequentially
counting multiple expressions listed through semicolons, returning the value of the last one. An example of such
an expression is "x = 2 * 2; y = 1 + 2; x^y + x", its value is 68. The values of temporary variables are not
stored and cannot be used in the following expressions.**
