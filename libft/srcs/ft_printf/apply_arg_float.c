/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:11:05 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 08:18:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	large_min_float(t_printf **lst, int len_str, int stock[3])
{
	char	*tmp;
	char	c;
	int		len;
	int		i;

	len = (*lst)->large_min - len_str;
	if (len > 0)
	{
		tmp = (char*)malloc(sizeof(char) * len);
		if (!tmp)
			return ;
		c = ' ';
		if (ft_strchr_exist((*lst)->options, '0') && stock[1] == 0)
			c = '0';
		i = -1;
		while (++i < len)
			tmp[i] = c;
		tmp[i] = '\0';
		ft_manage_display(lst, tmp);
		ft_strdel(&tmp);
	}
}

int	verif_float_zero(t_printf *lst)
{
	if (ft_strchr_exist(lst->options, '0'))
		return (1);
	return (0);
}

void	affiche_option(t_printf *lst, int neg, int stock[3], int place)
{
	char	c;
	int		space;

	c = 0;
	if (neg)
		stock[0] = 0;
	space = ft_strchr_exist(lst->options, ' ');
	if (neg || stock[0])
		space = 0;
	if (space == 1)
		c = ' ';
	if (stock[0])
		c = '+';
	if (neg)
		c = '-';
	if (c != 0)
	{
		if (place == 0 && stock[1] == 1)
			ft_putchar(c);
		if (place == 1 && stock[1] == 0 && verif_float_zero(lst))
			ft_putchar(c);
		if (place == 2 && stock[1] == 0 && verif_float_zero(lst) == 0)
			ft_putchar(c);
	}
}

void	affiche_hash(t_printf **lst, int stock[3], int place)
{
	if (ft_strchr_exist((*lst)->options, '#') \
			&& ((*lst)->precision == -1 || (*lst)->precision == 0))
	{
		if (place == 0 && stock[1] == 1)
			ft_putchar('.');
		else if (place == 1 && stock[1] == 0 \
				&& ft_strchr_exist((*lst)->options, '0') == 0)
			ft_putchar('.');
		else if (place == 2 && stock[1] == 0 \
				&& ft_strchr_exist((*lst)->options, '0'))
			ft_putchar('.');
	}
}

void	ft_apply_arg_float(char (*str)[BUF_S], t_printf **lst, int neg)
{
	char	*tmp;
	int		stock[3];
	int		len_str;

	ft_stock(lst, (*str), &stock);
	ft_inf_nan(str, lst, stock);
	tmp = ft_precision_float(str, lst);
	len_str = ft_strlen(tmp) + len_float(lst, stock, neg);
	affiche_option(*lst, neg, stock, 0);
	if (stock[1] == 1)
		ft_manage_display(lst, tmp);
	affiche_option(*lst, neg, stock, 1);
	affiche_hash(lst, stock, 0);
	large_min_float(lst, len_str, stock);
	affiche_option(*lst, neg, stock, 2);
	if (stock[1] == 0)
		ft_manage_display(lst, tmp);
	affiche_hash(lst, stock, 1);
	affiche_hash(lst, stock, 2);
	ft_strdel(&tmp);
}
