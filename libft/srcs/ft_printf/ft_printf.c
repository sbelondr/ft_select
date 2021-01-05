/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:39:03 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 00:52:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_del_lst(t_printf **lst)
{
	if (*lst)
	{
		ft_strdel(&((*lst)->format));
		free(*lst);
	}
}

void	check_overflow(t_printf **lst)
{
	if ((*lst)->len_data >= 1024)
	{
		write((*lst)->fd, (*lst)->data, 1024);
		ft_bzero((*lst)->data, 1024);
		(*lst)->len_data = 0;
	}
}

void	ft_printf_display(t_printf **lst)
{
	ft_bzero((*lst)->data, 1024);
	(*lst)->len_data = 0;
	while ((*lst)->format[(*lst)->index])
	{
		if ((*lst)->format[(*lst)->index] == '%')
		{
			ft_reset_value(lst);
			ft_manage(lst);
		}
		else
		{
			(*lst)->data[(*lst)->len_data] = (*lst)->format[(*lst)->index];
			(*lst)->len_data++;
			(*lst)->len++;
		}
		check_overflow(lst);
		(*lst)->index++;
	}
	write((*lst)->fd, (*lst)->data, 1024);
}

int	ft_printf(const char *format, ...)
{
	int			len;
	t_printf	*lst;

	if (ft_prepare(format, &lst) == 0)
		return (0);
	va_start((lst)->ap, format);
	ft_printf_display(&lst);
	va_end(lst->ap);
	len = lst->len;
	ft_del_lst(&lst);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int			len;
	t_printf	*lst;

	if (ft_prepare(format, &lst) == 0)
		return (0);
	lst->fd = fd;
	va_start((lst)->ap, format);
	ft_printf_display(&lst);
	va_end(lst->ap);
	len = lst->len;
	ft_del_lst(&lst);
	return (len);
}
