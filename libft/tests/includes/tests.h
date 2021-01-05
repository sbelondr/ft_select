/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:47:11 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 10:56:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "libft.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

Suite	*array_suite(void);
START_TEST(test_array);
Suite	*atoi_suite(void);

#endif
