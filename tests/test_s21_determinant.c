#include "test.h"

START_TEST(determinant1) {
    const int size = 5;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);

    m.matrix[0][0] = -1;
    m.matrix[0][1] = -4;
    m.matrix[0][2] = 0;
    m.matrix[0][3] = 0;
    m.matrix[0][4] = -2;
    m.matrix[1][0] = 0;
    m.matrix[1][1] = 1;
    m.matrix[1][2] = 1;
    m.matrix[1][3] = 5;
    m.matrix[1][4] = 4;
    m.matrix[2][0] = 3;
    m.matrix[2][1] = 1;
    m.matrix[2][2] = 7;
    m.matrix[2][3] = 1;
    m.matrix[2][4] = 0;
    m.matrix[3][0] = 0;
    m.matrix[3][1] = 0;
    m.matrix[3][2] = 2;
    m.matrix[3][3] = 0;
    m.matrix[3][4] = -3;
    m.matrix[4][0] = -1;
    m.matrix[4][1] = 0;
    m.matrix[4][2] = 4;
    m.matrix[4][3] = 2;
    m.matrix[4][4] = 2;


    double res = 0;
    int code = s21_determinant(&m, &res);

    ck_assert_double_eq_tol(res, 996, 1e-7);
    ck_assert_int_eq(code, OK);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
    const int size = 4;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            m.matrix[i][j] = j + i;

    double res = 0;
    int code = s21_determinant(&m, &res);
    ck_assert_double_eq_tol(res, 0.0, 1e-7);
    ck_assert_int_eq(code, OK);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
    const int size = 4;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = 6;
    m.matrix[0][1] = -2;
    m.matrix[0][2] = -1;
    m.matrix[0][3] = 5;
    m.matrix[1][0] = 8;
    m.matrix[1][1] = 7;
    m.matrix[1][2] = -9;
    m.matrix[1][3] = -7;
    m.matrix[2][0] = 15;
    m.matrix[2][1] = 35;
    m.matrix[2][2] = 3;
    m.matrix[2][3] = 5;
    m.matrix[3][0] = -1;
    m.matrix[3][1] = -11;
    m.matrix[3][2] = -2;
    m.matrix[3][3] = 1;

    double res = 0;
    int code = s21_determinant(&m, &res);
    ck_assert_double_eq_tol(res, 1101, 1e-07);
    ck_assert_int_eq(code, OK);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
    const int size = 3;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 3;
    m.matrix[0][2] = 1;
    m.matrix[1][0] = 7;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 1;
    m.matrix[2][0] = 9;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = 1;

    double res = 0;
    int code = s21_determinant(&m, &res);
    ck_assert_double_eq_tol(res, -32.0, 1e-07);
    ck_assert_int_eq(code, OK);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
    const int size = 2;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = -5;
    m.matrix[0][1] = -4;
    m.matrix[1][0] = -2;
    m.matrix[1][1] = -3;

    double res = 0;
    int code = s21_determinant(&m, &res);
    ck_assert_double_eq_tol(res, 7, 1e-07);
    ck_assert_int_eq(code, OK);

    s21_remove_matrix(&m);
}
END_TEST

Suite *suite_s21_determinant(void) {
    Suite *s = suite_create("suite_s21_determinant");
    TCase *tc = tcase_create("s21_determinant");

    tcase_add_test(tc, determinant1);
    tcase_add_test(tc, determinant2);
    tcase_add_test(tc, determinant3);
    tcase_add_test(tc, determinant4);
    tcase_add_test(tc, determinant5);

    suite_add_tcase(s, tc);
    return s;
}