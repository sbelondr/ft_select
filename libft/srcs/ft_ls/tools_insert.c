/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:24:33 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:51:57 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

int			verif_name(char *str, t_ls *ls)
{
	if (!str)
		return (-1);
	if (str[0] && str[0] == '.' && ft_strchr_exist(ls->flags, 'a') == 0)
		return (1);
	return (0);
}

long long	add_total(t_read **r)
{
	char		c;
	long long	len;

	c = (*r)->perm[0];
	len = (*r)->file_stat.st_blocks;
	return (len);
}

void		cnt_column(t_ls **ls, t_read *r)
{
	int	cnt;

	if (ft_numlen(r->file_stat.st_nlink) > (*ls)->column[1])
		(*ls)->column[1] = ft_numlen(r->file_stat.st_nlink);
	if (r->pwuser && (int)ft_strlen(r->pwuser->pw_name) > (*ls)->column[2])
		(*ls)->column[2] = ft_strlen(r->pwuser->pw_name);
	if ((int)ft_strlen(r->grpname->gr_name) > (*ls)->column[3])
		(*ls)->column[3] = ft_strlen(r->grpname->gr_name);
	if (r->perm[0] == 'b' || r->perm[0] == 'c')
	{
		cnt = ft_numlen(major(r->file_stat.st_rdev));
		(cnt > (*ls)->column[8]) ? (*ls)->column[8] = cnt : 0;
		cnt = ft_numlen(minor(r->file_stat.st_rdev));
		if (cnt > (*ls)->column[9])
			(*ls)->column[9] = cnt;
	}
	else
	{
		if (ft_numlen(r->file_stat.st_size) > (*ls)->column[4])
			(*ls)->column[4] = ft_numlen(r->file_stat.st_size);
	}
	if ((int)ft_strlen(r->jour) > (*ls)->column[6])
		(*ls)->column[6] = ft_strlen(r->jour);
	if ((int)ft_strlen(r->year_or_hours) > (*ls)->column[7])
		(*ls)->column[7] = ft_strlen(r->year_or_hours);
}

int			check_permission(t_read *r)
{
	int		i;

	i = 1;
	while (r->perm[i] == '-')
		i++;
	if (i == 10)
		return (0);
	return (1);
}

int			access_stat(t_ls **ls, t_read **r, int index)
{
	if ((stat((*ls)->options[index], &(*r)->file_stat)) < 0 &&
			lstat((*ls)->options[index], &(*r)->file_stat) < 0)
	{
		free((*r)->name);
		(*r)->name = NULL;
		free(*r);
		*r = NULL;
		return (1);
	}
	return (0);
}
