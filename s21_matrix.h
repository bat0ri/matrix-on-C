#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define OK 0
#define INCORRENTLY 1
#define CALC_ERROR 2

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;  // сама матрицы
  int rows;         // строки
  int columns;      // столбцы
} matrix_t;

// СОЗДАНИЕ МАТРИЦЫ
int s21_create_matrix(int rows, int columns, matrix_t *result);

// ОЧИСТКА МАТРИЦЫ
void s21_remove_matrix(matrix_t *A);

// СРАВНЕНИЕ МАТРИЦ
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// СУММА МАТРИЦ
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// РАЗНОСТЬ МАТРИЦ
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// УМНОЖЕНИЕ НА ЧИСЛО
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// УМНОЖЕНИЕ ДВУХ МАТРИЦ
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// ТРАНСПОНИРОВАНИЕ
int s21_transpose(matrix_t *A, matrix_t *result);

// АЛГЕБРАИЧЕСКИЕ ДОПОЛНЕНИЯ
int s21_calc_complements(matrix_t *A, matrix_t *result);

// double deter(matrix_t *A, int n);

// ОПРЕДЕЛИТЕЛЬ
int s21_determinant(matrix_t *A, double *result);

void s21_minor(matrix_t *A, int tmp_i, int tmp_j, matrix_t *result);

// ОБРАТНАЯ МАТРИЦА
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_