#include "libft.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

START_TEST(test_ft_atoi) {
  ck_assert_uint_eq(ft_atoi("2"), 2);
  printf(" [PASS] Test: 2 \n");

  ck_assert_uint_eq(ft_atoi("0"), 0);
  printf(" [PASS] Test: 0 \n");

  ck_assert_uint_eq(ft_atoi("25"), 25);
  printf(" [PASS] Test: 25 \n");

  ck_assert_uint_eq(ft_atoi("-123"), -123);
  printf(" [PASS] Test: -123 \n");
} END_TEST

Suite *atoi_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("ft_atoi");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_ft_atoi);
  suite_add_tcase(s, tc_core);

  return s;
}
