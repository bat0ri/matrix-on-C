#include "test.h"

START_TEST(sum_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx = {0};
    s21_create_matrix(rows, cols, &mtx);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(-6e6, 6e6);
            mtx.matrix[i][j] = get_rand(-6e6, 6e6);
            check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
        }
    }
    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(sum_matrix_error) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    matrix_t mtx = {0};
    s21_create_matrix(rows, cols, &mtx);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
        }
    }
    matrix_t res = {0};
    
    ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), INCORRENTLY);

    // s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
}
END_TEST

Suite *suite_s21_sum_matrix(void) {
    Suite *s = suite_create("suite_s21_sum_matrix");
    TCase *tc = tcase_create("s21_sum_matrix");

    tcase_add_loop_test(tc, sum_matrix, 0, 100);
    tcase_add_test(tc, sum_matrix_error);

    suite_add_tcase(s, tc);
    return s;
}
