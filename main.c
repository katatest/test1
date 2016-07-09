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
	char *here = NULL;

	s = numerals_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	num_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	//radd("II", "III");
	//radd("IV", "V");

	for(int i = 1000; i < 1100; i++) {
		here = strdup(int_to_nume(i));
		printf(">>>>>>>>>> %d : %s\n", i, here);
		free(here);
	}	

	//here = strdup(int_to_nume(60));
	//printf(">>>>>>>>>> %d : %s\n", 60, here);
	//free(here);

    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

