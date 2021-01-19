/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_n_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:13:24 by sbelondr          #+#    #+#             */
/*   Updated: 2021/01/19 10:15:36 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			add_length(t_printf **lst, int neg, int stock[3], int len_str)
{
	if (neg || stock[0] || ft_strchr_exist((*lst)->options, ' '))
		len_str += 1;
	return (len_str);
}

int			ft_condition_option(int stock, t_printf **lst)
{
	if (stock == 0 && (ft_strchr_exist((*lst)->options, '0') == 0 \
				|| (ft_strchr_exist((*lst)->options, '0') \
					&& (*lst)->precision != -2)))
		return (1);
	return (0);
}
