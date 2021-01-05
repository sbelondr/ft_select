/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:48:57 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 10:55:23 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"

START_TEST(test_array) {

	int	res = 0;
	int	check = 0;

	res = ft_atoi("2");
	check = 2;
	ck_assert_msg(res == check,
         "We have to find %d but we have %d", check, res);
	printf(" [PASS] Test: 2 \n");

	ck_assert_uint_eq(ft_atoi("0"), 0);
	printf(" [PASS] Test: 0 \n");

	ck_assert_uint_eq(ft_atoi("25"), 25);
	printf(" [PASS] Test: 25 \n");

	ck_assert_uint_eq(ft_atoi("-123"), -123);
	printf(" [PASS] Test: -123 \n");
} END_TEST

Suite *array_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("array");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_array);
	suite_add_tcase(s, tc_core);

	return s;
}
