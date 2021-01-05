/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 07:11:11 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 00:41:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_arg_array_s(t_printf **lst)
{
	char	**lst_str;

	lst_str = ft_arraydup(va_arg((*lst)->ap, char**));
	if (!lst_str)
		lst_str = ft_arraydup(NULL);
	ft_arraydisplay(lst_str);
	ft_arraydel(&lst_str);
}

void	ft_arg_s(t_printf **lst)
{
	char	*str;

	str = ft_strdup(va_arg((*lst)->ap, char*));
	if (!str)
		str = ft_strdup("(null)");
	apply_arg_s(str, &(*lst));
	ft_strdel(&str);
}

void	ft_arg_c(t_printf **lst)
{
	char	c;

	c = (char)(va_arg((*lst)->ap, int));
	if (!c)
	{
		(*lst)->len += 1;
		apply_arg_c(0, &(*lst));
	}
	else
		apply_arg_c(c, &(*lst));
}

void	ft_arg_percent(t_printf **lst)
{
	char	c;

	c = '%';
	apply_arg_c(c, &(*lst));
}
