#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "roman.h"

START_TEST(junk)
{
	ck_assert_int_eq(1, 1);
	ck_assert_int_eq(0, 1);
}
END_TEST

Suite *numerals_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Numerals");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, junk);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char *argv[])
{
	int num_failed;
	Suite *s;
	SRunner *sr;

	s = numerals_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	num_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	radd("II", "III");
	radd("IV", "V");
	printf("%d\n", nume_to_int("V"));
	printf("%s\n", int_to_nume(1245));

	//return 0;
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

