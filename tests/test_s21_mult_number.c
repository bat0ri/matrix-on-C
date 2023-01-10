#include "test.h"

START_TEST(mult_number_matrix) {
    const int rows = rand() % 100 + 1;
    const int cols = rand() % 100 + 1;
    matrix_t m = {0};
    s21_create_matrix(rows, cols, &m);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);
    double mult_number = get_rand(-6e6, 6e6);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(6e6, 6e6);
            check.matrix[i][j] = m.matrix[i][j] * mult_number;
        }
    }
    matrix_t res = {0};
    int a = s21_mult_number(&m, mult_number, &res);

    ck_assert_int_eq(a, OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
    s21_remove_matrix(&m);
}
END_TEST

// START_TEST(test2) {
//     double number = INFINITY;
//     const int rows = rand() % 100 + 1;
//     const int cols = rand() % 100 + 1;
//     matrix_t m = {0};
//     s21_create_matrix(rows, cols, &m);

//     matrix_t res = {0};
//     int a = s21_mult_number(&m, number, &res);
//     ck_assert_int_eq(a, INCORRENTLY);
//     s21_remove_matrix(&m);
//     s21_remove_matrix(&res);
// }
// END_TEST

Suite *suite_s21_mult_number_matrix(void) {
    Suite *s = suite_create("suite_s21_mult_number_matrix");
    TCase *tc = tcase_create("s21_mult_number_matrix");

    tcase_add_loop_test(tc, mult_number_matrix, 0, 10);
    //tcase_add_test(tc, test2);

    suite_add_tcase(s, tc);
    return s;
}
