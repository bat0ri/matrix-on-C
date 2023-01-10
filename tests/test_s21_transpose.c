#include "test.h"

START_TEST(transpose_matrix) {
    int rows = rand() % 100 + 1;
    int cols = rand() % 100 + 1;
    matrix_t m ;
    s21_create_matrix(rows, cols, &m);

    matrix_t check;
    s21_create_matrix(cols, rows, &check);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double rand_val = get_rand(-10e10, 10e10);
            m.matrix[i][j] = rand_val;
            check.matrix[j][i] = rand_val;
        }
    }

    matrix_t res;
    ck_assert_int_eq(s21_transpose(&m, &res), OK);
    //ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST
Suite *suite_s21_transpose_matrix(void) {
    Suite *s = suite_create("suite_s21_transpose_matrix");
    TCase *tc = tcase_create("s21_transpose_matrix");

    tcase_add_loop_test(tc, transpose_matrix, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}