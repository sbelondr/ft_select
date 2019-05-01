/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:13:43 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:50:04 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

int		init_ls(t_ls **ls)
{
	int	i;

	i = -1;
	if (!((*ls) = (t_ls*)malloc(sizeof(t_ls) * 1)))
		return (-1);
	(*ls)->options = NULL;
	(*ls)->rep = 0;
	ft_bzero(&(*ls)->flags, 10);
	(*ls)->total = 0;
	(*ls)->read_file = 0;
	while (++i < 10)
		(*ls)->column[i] = 0;
	(*ls)->column[0] = 1;
	(*ls)->column[5] = 3;
	return (0);
}

int		remove_ls(t_ls **ls, int len)
{
	t_ls	*tontruc;

	tontruc = *ls;
	if (len == 0)
		free(tontruc->options[0]);
	free(tontruc->options);
	free(*ls);
	return (0);
}

void	ft_dirdel(DIR **check)
{
	closedir(*check);
	(*check) = NULL;
}

int		init_srt_options(t_ls **ls, int len)
{
	int		srt_options[len];
	int		i;
	int		stock;

	i = -1;
	while (++i < len)
		srt_options[i] = i;
	stock = first_sort_options(&(*ls), len, srt_options);
	return (stock);
}
