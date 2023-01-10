#include "s21_matrix.h"

// СОЗДАНИЕ МАТРИЦЫ И ЗАПОЛНЕНИЕ
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows > 0 && columns > 0) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
    return OK;
  } else {
    return INCORRENTLY;
  }
}

// ОЧИСТКА МАТРИЦЫ
void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

// СРАВНЕНИЕ МАТРИЦ
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int b = FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) {
    b = SUCCESS;
    for (int i = 0; i < A->rows && b != FAILURE; i++)
      for (int j = 0; j < A->columns && b != FAILURE; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          b = FAILURE;
        }
  }
  return b;
}

// СУММА МАТРИЦ
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      result->columns = A->columns;
      result->rows = A->rows;
      result->matrix = (double **)malloc(A->rows * sizeof(double *));
      for (int i = 0; i < A->rows; i++) {
        result->matrix[i] = (double *)malloc(A->columns * sizeof(double));
      }
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      return OK;
    } else {
      return CALC_ERROR;
    }
  } else {
    return INCORRENTLY;
  }
}

// ВЫЧИТАНИЕ МАТРИЦЫ (ИЗ А ВЫЧИТАЕМ В)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      result->columns = A->columns;
      result->rows = A->rows;
      result->matrix = (double **)malloc(A->rows * sizeof(double *));
      for (int i = 0; i < A->rows; i++) {
        result->matrix[i] = (double *)malloc(A->columns * sizeof(double));
      }
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      return OK;
    } else {
      return CALC_ERROR;
    }
  } else {
    return INCORRENTLY;
  }
}

// УМНОЖЕНИЕ НА ЧИСЛО
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    // s21_show_matrix(result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    return OK;
  } else {
    return INCORRENTLY;
  }
}

// УМНОЖЕНИЕ МАТРИЦ
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->columns == B->rows) {
      result->rows = 0;
      // s21_remove_matrix(result);
      result->rows = A->rows;
      result->columns = B->columns;
      result->matrix = (double **)malloc(A->rows * sizeof(double *));
      for (int i = 0; i < A->rows; i++) {
        result->matrix[i] = (double *)malloc(B->columns * sizeof(double));
      }
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      return OK;
    } else {
      result->rows = 0;
      return CALC_ERROR;
    }
  } else {
    return INCORRENTLY;
  }
}

// ТРАСПОНИРОВАНИЕ
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A->columns > 0 && A->columns > 0) {
    result->columns = A->rows;
    result->rows = A->columns;
    result->matrix = (double **)malloc(result->rows * sizeof(double *));
    for (int i = 0; i < result->rows; i++) {
      result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
    }
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[j][i];
    return OK;
  } else {
    return INCORRENTLY;
  }
}

// МИНОР МАТРИЦЫ
void s21_minor(matrix_t *A, int tmp_i, int tmp_j, matrix_t *result) {
  int n = A->rows - 1;
  result->columns = n;
  result->rows = n;
  result->matrix = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    result->matrix[i] = (double *)malloc(n * sizeof(double));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tmp_i > i && tmp_j > j) {
        result->matrix[i][j] = A->matrix[i][j];
      }
      if (tmp_i <= i && tmp_j > j) {
        result->matrix[i][j] = A->matrix[i + 1][j];
      }
      if (tmp_i > i && tmp_j <= j) {
        result->matrix[i][j] = A->matrix[i][j + 1];
      }
      if (tmp_i <= i && tmp_j <= j) {
        result->matrix[i][j] = A->matrix[i + 1][j + 1];
      }
    }
  }
}

double deter(matrix_t *A, int n) {
  if (n == 1) {
    return A->matrix[0][0];
  } else if (n == 2) {
    return (A->matrix[0][0] * A->matrix[1][1] -
            (A->matrix[1][0] * A->matrix[0][1]));
  } else {
    double d = 0;
    for (int i = 0; i < n; i++) {
      matrix_t M;
      s21_minor(A, 0, i, &M);
      d += pow(-1, i + 2) * A->matrix[0][i] * deter(&M, n - 1);
      s21_remove_matrix(&M);
    }
    return d;
  }
}

// ОПРЕДЕЛИТЕЛЬ МАТРИЦЫ
int s21_determinant(matrix_t *A, double *result) {
  if (A->rows == A->columns) {
    *result = deter(A, A->rows);
    return OK;
  } else {
    return CALC_ERROR;
  }
}

//  МАТРИЦА МИНОРОВ И АЛГЕБРАИЧЕСКИХ ДОПОЛНЕНИЙ
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows > 1 && A->columns > 1 && A->rows == A->columns) {
      result->rows = A->rows;
      result->columns = A->rows;
      result->matrix = (double **)malloc(result->rows * sizeof(double *));
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
      }
      matrix_t M;
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          s21_minor(A, i, j, &M);
          s21_determinant(&M, &result->matrix[i][j]);
          if ((i + j) % 2 != 0) {
            result->matrix[i][j] *= -1;
          }
          s21_remove_matrix(&M);
        }
      }
      return OK;
    } else {
      return CALC_ERROR;
    }
  } else {
    return INCORRENTLY;
  }
}

// ОБРАТНАЯ МАТРИЦА --------------------------------------> LEAKS
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      result->rows = A->rows;
      result->columns = A->rows;
      result->matrix = (double **)malloc(result->rows * sizeof(double *));
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
      }
      double d;
      s21_determinant(A, &d);
      if (d != 0) {
        if (A->rows > 1) {
          matrix_t M;
          s21_calc_complements(A, &M);
          matrix_t T;
          s21_transpose(&M, &T);
          s21_mult_number(&T, 1. / d, result);
          s21_remove_matrix(&T);
          s21_remove_matrix(&M);
          return OK;
        } else {
          result->matrix[0][0] = 1. / A->matrix[0][0];
          return OK;
        }
      } else {
        s21_remove_matrix(result);
        return CALC_ERROR;
      }
    } else {
      return CALC_ERROR;
    }
  } else {
    return INCORRENTLY;
  }
}
