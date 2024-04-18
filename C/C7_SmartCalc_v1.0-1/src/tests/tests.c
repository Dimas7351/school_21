#include "tests.h"

START_TEST(ln_cos) {
    char *equation = "ln(cos(x))";
    double answer = 0;
    int status = calculate(equation, PI, &answer);
    double result = 0.0;
    ck_assert_double_eq_tol(result, answer, 1e-7);
    ck_assert_int_eq(status, FAILED_CALC);
}

START_TEST(ln_sin) {
    char *equation = "ln(sin(x))";
    double answer = 0;
    int status = calculate(equation, PI / 2, &answer);
    double result = 0;
    ck_assert_double_eq_tol(result, answer, 1e-7);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(ln_sin_incorrect_input) {
    char *equation = "ln(sin(x)))";
    int length = 0;
    token *infix = get_tokens(equation, &length);
    ck_assert_ptr_null(infix);
}

START_TEST(sin_sqrt_4) {
    char *equation = "sin(sqrt(4))";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 0.909297;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(simple_arithm) {
    char *equation = "1 + 2 + 4 * 3 - 3 * 7";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = -6;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(simple_arithm_2) {
    char *equation = "(1 + 2 + 4 * 3 - 3 * 7) / 4";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = -1.5;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(stress_test) {
    char *equation =
        "acos(cos(sin(atan(ln(sqrt((8 * ((1 + 2 + 4 * 3 - 3 * 7) / "
        "4)) + 133))))))";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 0.922957;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(unary) {
    char *equation = "(-4 + 5) * 2";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 2;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(degree) {
    char *equation = "2.5 ^ 2";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 6.25;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(degree_tan) {
    char *equation = "tan(2.5 ^ 2.5)";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 0.49140;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(mod) {
    char *equation = "6.25 mod 3";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 0.25;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(asin_degree_mod) {
    char *equation = "asin(0.2)";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    double result = 0.201358;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, SUCCESS);
}

START_TEST(brackets) {
    char *equation = "()";
    double answer = 0;
    int status = calculate(equation, DUMMY_DOUBLE, &answer);
    ck_assert_int_eq(status, FAILED_CALC);
}

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Calculations");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, ln_cos);
    tcase_add_test(tc1_1, ln_sin);
    tcase_add_test(tc1_1, ln_sin_incorrect_input);
    tcase_add_test(tc1_1, sin_sqrt_4);
    tcase_add_test(tc1_1, simple_arithm);
    tcase_add_test(tc1_1, simple_arithm_2);
    tcase_add_test(tc1_1, stress_test);
    tcase_add_test(tc1_1, unary);
    tcase_add_test(tc1_1, degree);
    tcase_add_test(tc1_1, degree_tan);
    tcase_add_test(tc1_1, mod);
    tcase_add_test(tc1_1, brackets);
    tcase_add_test(tc1_1, asin_degree_mod);

    srunner_run_all(sr, CK_ENV);
    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
