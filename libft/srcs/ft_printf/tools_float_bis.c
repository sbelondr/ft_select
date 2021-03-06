/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:33:50 by sbelondr          #+#    #+#             */
/*   Updated: 2021/01/19 10:03:41 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_precision_float(char (*dst)[BUF_S], t_printf **lst)
{
	char	*tmp;

	tmp = ft_round_precision(dst, (*lst)->precision);
	if ((*lst)->precision != -2 && ft_strchr_exist((*lst)->options, '#'))
		(*dst)[ft_strlen(*dst)] = '.';
	return (tmp);
}

int			check_p(char dst[BUF_S], int precision, int i)
{
	int	stock;

	if ((int)ft_strlen(dst) > precision && dst[i + precision + 1])
		stock = dst[i + precision + 1] - '0';
	else
		stock = 0;
	return (stock);
}

static int	ft_fuck_norm(char (*dst)[BUF_S], int i, int *stock)
{
	*stock = 0;
	if ((*dst)[i + 2] - '0' == 0)
		*stock = 1;
	*stock = ((*dst)[i + 1] - '0') - (*stock);
	while ((*dst)[i])
		(*dst)[i++] = '\0';
	return (i);
}

char		*ft_round_precision(char (*dst)[BUF_S], int precision)
{
	int		i;
	int		j;
	int		stock;
	char	*tmp;

	if (precision == -2)
		precision = 6;
	i = 0;
	j = 0;
	stock = -1;
	while ((*dst)[i] && (*dst)[i] != '.')
		i++;
	if (precision == 0 || precision == -1)
		i = ft_fuck_norm(dst, i, &stock);
	else
		while ((*dst)[i + j] && j < precision)
			j++;
	if (stock == -1)
		stock = check_p((*dst), precision, i);
	i += j;
	(*dst)[++i] = '\0';
	tmp = ft_apply_round(dst, stock, precision);
	return (tmp);
}

int			len_float(t_printf **lst, int stock[3], int neg)
{
	int	len;

	len = 0;
	if (neg)
		(*lst)->len += 1;
	if (neg || stock[0] || ft_strchr_exist((*lst)->options, ' '))
		len += 1;
	if (ft_strchr_exist((*lst)->options, '#') && ((*lst)->precision == -1 \
				|| (*lst)->precision == 0))
		len += 1;
	return (len);
}
