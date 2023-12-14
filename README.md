# matrix-on-C

# Matrix Library

This Makefile is designed to build a library for matrix operations in C using the specified CFLAGS and source files.

## Makefile Usage

### Targets

- **all**: Removes existing object files and builds the library.
- **test**: Compiles the test suite and executes it.
- **clean**: Removes generated files and formats code.
- **check**: Executes various checks including memory checks (valgrind/leaks), code style checks (cppcheck, clang-format), and memory leaks detection (valgrind/leaks).
- **gcov_report**: Generates a code coverage report using gcovr.

### Description

This library is designed for matrix operations in C, providing functions for:

- Creating matrices.
- Clearing matrices.
- Comparing matrices.
- Matrix addition and subtraction.
- Scalar multiplication of matrices.
- Matrix multiplication.
- Transposition of matrices.
- Calculating matrix determinants, inverse matrices, and more.

## Matrix Library Description

The provided header file `s21_matrix.h` contains function prototypes for matrix operations:

```c
// Function prototypes for matrix operations

// Functions for creating, removing, and comparing matrices
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Functions for matrix arithmetic
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Other matrix operations
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
