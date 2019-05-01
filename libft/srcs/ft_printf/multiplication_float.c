/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication_float.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:37:08 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:48:40 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	tablo_calc(char (*tab)[BUF_S], int base)
{
	int		i;
	int		stock;

	i = ft_strlen(*tab);
	stock = 0;
	while (--i >= 0)
	{
		stock += (((*tab)[i] - '0') * base);
		(*tab)[i] = (stock % 10) + '0';
		if (stock != 0)
		{
			stock /= 10;
			if (i == 0 && stock != 0)
			{
				ft_deplace(&(*tab));
				(*tab)[i] = stock + '0';
			}
		}
	}
}

void	mult_mantissa(char (*tab)[BUF_S], int d)
{
	int	i;

	i = -1;
	while (++i <= d)
		tablo_calc(&(*tab), 2);
}
