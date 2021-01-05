/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:49:36 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 10:54:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"


int main(void) {
	int	no_failed = 0;
	SRunner *runner;

	runner = srunner_create(atoi_suite());
	srunner_run_all(runner, CK_NORMAL);
	no_failed += srunner_ntests_failed(runner);
	srunner_free(runner);

	runner = srunner_create(array_suite());
	srunner_run_all(runner, CK_NORMAL);
	no_failed += srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
