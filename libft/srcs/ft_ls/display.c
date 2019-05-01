/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:44:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:49:02 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

void	space_line(int nb_space)
{
	int		i;
	char	buff[nb_space + 1];

	i = -1;
	nb_space++;
	ft_bzero(buff, nb_space);
	while (++i < nb_space)
		buff[i] = 32;
	buff[i] = '\0';
	ft_putstr(buff);
}

void	verif_space_line(int nb_space)
{
	if (nb_space < 1)
		space_line(0);
	else
		space_line(nb_space);
}

void	display_normal_mode(t_read *r, int is_s)
{
	if (is_s)
		ft_printf("%d\t", r->file_stat.st_blocks);
	ft_printf("%s\n", r->name);
}

void	display_read(t_ls *ls, t_save *sv, int break_line)
{
	int	is_s;

	is_s = ft_strchr_exist(ls->flags, 's');
	ft_sort_ls(&sv, &ls);
	first_sv(sv);
	if (ft_strchr_exist(ls->flags, 'l'))
	{
		(break_line != -1) ? ft_printf("total %d\n", ls->total) : 0;
		while (sv->list != NULL)
		{
			display_read_l(sv->list, is_s, ls);
			next_sv(sv);
		}
	}
	else
	{
		while (sv->list != NULL)
		{
			display_normal_mode(sv->list, is_s);
			next_sv(sv);
		}
	}
}
