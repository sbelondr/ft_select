/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 09:29:49 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 08:35:08 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convert_base_u64(t_u64 nb, int base, char (*str)[BUF_S])
{
	t_u64	result;
	char	test[BUF_S];
	char	c;
	int		i;

	ft_bzero(str, BUF_S);
	ft_bzero(&test, BUF_S);
	i = 0;
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		test[i++] = ft_binary_to_char(result);
		ft_startjoin(str, c);
	}
	ft_cpy_str(str, test);
}

void	ft_float_to_bin(char (*str)[BUF_S], int d, t_u64 mantissa)
{
	ft_bzero(str, BUF_S);
	ft_convert_base_u64(mantissa, 2, str);
	ft_gest_float(str, d);
}

static int	ft_fuck_norm(t_u64 cp, t_u64 mantissa, char (*str)[BUF_S])
{
	int	d;

	d = ((cp << 1) >> 53) - 1023;
	if (d == 1024 && mantissa == 0)
	{
		if (cp >> 63)
			ft_cpy_str(str, "-inf");
		else
			ft_cpy_str(str, "inf");
	}
	if (d == 1024)
	{
		if (cp >> 63)
			ft_cpy_str(str, "-nan");
		else
			ft_cpy_str(str, "nan");
	}
	return (d);
}

/*
** mantissa = valeur binaire
** d = nb de chiffre avant virgule (en binaire)
*/

void	ft_float(double nb, char (*str)[BUF_S], int *neg)
{
	t_u64	cp;
	t_u64	mantissa;
	int		d;

	cp = *(t_u64*)(&nb);
	mantissa = ((cp << 12) >> 12);
	d = ft_fuck_norm(cp, mantissa, str);
	if (cp >> 63 && d == 1024)
		return ;
	if (d != -1023)
		mantissa |= 0x10000000000000;
	else
	{
		if (nb == 0.0f)
			d = 0;
		else
			d = d + 1;
	}
	ft_float_to_bin(str, d, mantissa);
	if (cp >> 63)
		*neg = 1;
}

void	ft_arg_float(t_printf **lst)
{
	char	str[BUF_S];
	double	nb;
	int		neg;

	neg = 0;
	nb = (double)va_arg((*lst)->ap, double);
	ft_float(nb, &str, &neg);
	ft_apply_arg_float(&str, lst, neg);
}
