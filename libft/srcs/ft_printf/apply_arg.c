/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 08:49:06 by sbelondr          #+#    #+#             */
/*   Updated: 2021/01/19 09:59:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_fuck_norm(char (*dst)[BUF_S], t_printf *lst)
{
	if (ft_strcmp(*dst, "0\0") == 0 && ft_strchr_exist(lst->options, '0') == 0 \
			&& (lst->large_min == 0 || (lst->precision == -1 \
					|| lst->precision == 0)))
		return (1);
	return (0);
}

void		ft_large_min(char (*dst)[BUF_S], t_printf *lst, int stock[3])
{
	char	c;
	int		i;
	char	tmp[BUF_S];

	i = -1;
	c = ' ';
	if (ft_strchr_exist(lst->options, '0') && lst->precision < 0)
		c = '0';
	if (ft_fuck_norm(dst, lst))
		ft_bzero(dst, BUF_S);
	if (stock[2] > 0)
	{
		if (ft_strchr_exist(lst->options, '-'))
			while (stock[2]-- > 0)
				(*dst)[ft_strlen(*dst) + stock[2]] = ' ';
		else
		{
			while (stock[2] > ++i)
				tmp[i] = c;
			i = 0;
			while (stock[2] < BUF_S)
				tmp[stock[2]++] = (*dst)[i++];
			ft_cpy_str(&(*dst), tmp);
		}
	}
}

/*
**	stock[0] = plus
**	stock[1] = moins
**	stock[2] = len
*/
