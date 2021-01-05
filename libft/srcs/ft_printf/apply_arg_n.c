/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:02:59 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 08:11:55 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	options_n(t_printf **lst, int stock[3], int neg, int rd)
{
	char	c;
	int		space;

	c = 0;
	if (neg)
		stock[0] = 0;
	space = ft_strchr_exist((*lst)->options, ' ');
	if (neg || stock[0])
		space = 0;
	if (space == 1)
		c = ' ';
	if (stock[0])
		c = '+';
	if (neg)
		c = '-';
	if (c != 0 && rd == 1)
	{
		(*lst)->len += 1;
		write(1, &c, 1);
	}
}

static char	*ft_fuck_norm(int len[2], char *dst)
{
	char	*tmp;
	char	*tmp_b;

	len[0] = -1;
	tmp_b = (char*)malloc(sizeof(char) * len[1] + 1);
	if (!tmp_b)
		return (NULL);
	while (++len[0] < len[1])
		tmp_b[len[0]] = '0';
	tmp_b[len[0]] = '\0';
	tmp = ft_strjoin(tmp_b, dst);
	ft_strdel(&tmp_b);
	return (tmp);
}

char	*precision_n(char *str, t_printf **lst, int neg)
{
	int		len[2];
	char	*tmp;
	char	*dst;

	if (neg)
		dst = ft_strsub(str, 1, ft_strlen(str));
	else
		dst = ft_strdup(str);
	if (!dst)
		return (NULL);
	if ((dst[0] == '0') && ((*lst)->precision == -1 || (*lst)->precision == 0))
		dst[0] = 0;
	len[1] = (*lst)->precision - ft_strlen(dst);
	if (len[1] > 0)
		tmp = ft_fuck_norm(len, dst);
	else
		tmp = ft_strdup(dst);
	ft_strdel(&dst);
	return (tmp);
}

void	large_min_n(t_printf **lst, int len_str, int stock[3])
{
	int		i;
	int		len;
	char	c;
	char	*tmp;

	len = (*lst)->large_min - len_str;
	if (len > 0)
	{
		i = -1;
		c = ' ';
		if (ft_strchr_exist((*lst)->options, '0') && stock[1] == 0 \
				&& (*lst)->precision == -2)
			c = '0';
		tmp = (char*)malloc(sizeof(char) * len + 1);
		if (!tmp)
			return ;
		while (++i < len)
			tmp[i] = c;
		tmp[i] = '\0';
		ft_manage_display(lst, tmp);
		ft_strdel(&tmp);
	}
}

int	add_length(t_printf **lst, int neg, int stock[3], int len_str)
{
	if (neg || stock[0] || ft_strchr_exist((*lst)->options, ' '))
		len_str += 1;
	return (len_str);
}

void	apply_arg_n(char *str, t_printf **lst)
{
	char	*tmp;
	int		len_str;
	int		neg;
	int		stock[3];

	neg = ft_strchr_exist(str, '-');
	if (neg)
		stock[0] = 0;
	ft_stock(&(*lst), str, &stock);
	if (stock[1] == 1)
		options_n(lst, stock, neg, 1);
	tmp = precision_n(str, lst, neg);
	if (stock[1] == 1)
		ft_manage_display(lst, tmp);
	len_str = ft_strlen(tmp);
	len_str = add_length(lst, neg, stock, len_str);
	if (stock[1] == 0 && ft_strchr_exist((*lst)->options, '0') \
			&& (*lst)->precision == -2)
		options_n(lst, stock, neg, 1);
	large_min_n(lst, len_str, stock);
	if (stock[1] == 0 && (ft_strchr_exist((*lst)->options, '0') == 0 \
				|| (ft_strchr_exist((*lst)->options, '0') \
					&& (*lst)->precision != -2)))
		options_n(&(*lst), stock, neg, 1);
	if (stock[1] == 0)
		ft_manage_display(lst, tmp);
	ft_strdel(&tmp);
}
