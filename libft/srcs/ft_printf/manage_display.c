/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:26:04 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 00:18:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write_printf(t_printf **lst)
{
	if ((*lst)->len_data >= 1024)
	{
		write((*lst)->fd, (*lst)->data, 1024);
		ft_bzero((*lst)->data, 1024);
		(*lst)->len_data = 0;
	}
}

void	ft_manage_display(t_printf **lst, char *str)
{
	size_t	len;
	int		index;

	len = ft_strlen(str);
	(*lst)->len += len;
	index = 0;
	while (len > 0)
	{
		while ((*lst)->len_data < 1024 && len > 0)
		{
			(*lst)->data[(*lst)->len_data] = str[index];
			++index;
			(*lst)->len_data++;
			--len;
		}
		ft_write_printf(lst);
	}
	ft_write_printf(lst);
}
