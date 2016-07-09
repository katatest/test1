#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "roman.h"

/**
 * Test adding a bunch of numbers.
 */
START_TEST(addition)
{
    ck_assert_str_eq(radd("I", "II"), "III");
    ck_assert_str_eq(radd("I", "V"), "VI");
    ck_assert_str_eq(radd("CLXXIII", "LXIV"), "CCXXXVII");
    ck_assert_str_eq(radd("CCXXXVII", "MCCXXXVIII"), "MCDLXXV");
    ck_assert_str_eq(radd("C1X", "XCIX"), "Error: Non-roman numerals present");
    ck_assert_str_eq(radd("0", "0"), "Error: Non-roman numerals present");
}
END_TEST

/**
 * Test subtracting a bunch of numbers.
 */
START_TEST(subtraction)
{
    ck_assert_str_eq(rsubtract("X", "V"), "VI");
    ck_assert_str_eq(rsubtract("X", "V"), "V");
    ck_assert_str_eq(rsubtract("XIII", "VI"), "VII");
    ck_assert_str_eq(rsubtract("CIX", "XCIX"), "X");
    ck_assert_str_eq(rsubtract("L", "L"), "Error: No Zeros");
    ck_assert_str_eq(rsubtract("X", "L"), "Error: No Negatives");
    ck_assert_str_eq(rsubtract("19", "X"), "Error: Non-roman numerals present");
    ck_assert_str_eq(rsubtract("Yo Momma", "X"), "Error: Non-roman numerals present");
}
END_TEST

Suite *numerals_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Numerals");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, subtraction);
    tcase_add_test(tc_core, addition);

    suite_add_tcase(s, tc_core);

    return s;
}

/**
 *
 */
int main(int argc, char *argv[])
{
    int num_failed;
    Suite *s;
    SRunner *sr;

	printf("\n--------------------------------\n");
	printf("Running test suite for libroman.\n");
	printf("--------------------------------\n\n");

    s = numerals_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

	if(num_failed == 0) {
		printf("\nAll Passed...\n\n");
	} else {
		printf("\nErrors...\n\n");
	}

	printf("\n--------------------------------\n\n");

    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

