/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:31:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 10:47:56 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

char		type_file(t_read *r)
{
	if (S_ISREG(r->file_stat.st_mode))
		return ('-');
	else if (S_ISDIR(r->file_stat.st_mode))
		return ('d');
	else if (S_ISLNK(r->file_stat.st_mode))
		return ('l');
	else if (S_ISBLK(r->file_stat.st_mode))
		return ('b');
	else if (S_ISCHR(r->file_stat.st_mode))
		return ('c');
	else if (S_ISSOCK(r->file_stat.st_mode))
		return ('s');
	else if (S_ISFIFO(r->file_stat.st_mode))
		return ('p');
	else
		return ('~');
}

void		make_other_perm(t_read **r)
{
	int	i;
	int	min;

	i = 0;
	min = 0;
	while ((*r)->perm[++i])
		if ((*r)->perm[i] != '-')
		{
			min = 1;
			break ;
		}
	if (S_ISVTX & (*r)->file_stat.st_mode)
		(*r)->perm[9] = (min) ? 't' : 'T';
	if (S_ISGID & (*r)->file_stat.st_mode)
		(*r)->perm[6] = (min) ? 's' : 'S';
	if (S_ISUID & (*r)->file_stat.st_mode)
		(*r)->perm[3] = (min) ? 's' : 'S';
}

void		make_perm(t_read **r, t_ls *ls)
{
	int		i;
	int		verif;

	i = 1;
	ft_bzero(&((*r)->symbolic_link), BUF_S);
	if ((ls->read_file && ls->read_file->d_type == DT_LNK) ||
			S_ISLNK((*r)->file_stat.st_mode))
	{
		(lstat((*r)->path, &(*r)->file_stat)) > 0 ? error_see() : 0;
		verif = readlink((*r)->path, (*r)->symbolic_link, BUF_S);
		if (verif < 0)
			readlink((*r)->name, (*r)->symbolic_link, BUF_S);
	}
	(*r)->perm[0] = type_file(*r);
	(*r)->perm[i++] = S_IRUSR & (*r)->file_stat.st_mode ? 'r' : '-';
	(*r)->perm[i++] = S_IWUSR & (*r)->file_stat.st_mode ? 'w' : '-';
	(*r)->perm[i++] = S_IXUSR & (*r)->file_stat.st_mode ? 'x' : '-';
	(*r)->perm[i++] = S_IRGRP & (*r)->file_stat.st_mode ? 'r' : '-';
	(*r)->perm[i++] = S_IWGRP & (*r)->file_stat.st_mode ? 'w' : '-';
	(*r)->perm[i++] = S_IXGRP & (*r)->file_stat.st_mode ? 'x' : '-';
	(*r)->perm[i++] = S_IROTH & (*r)->file_stat.st_mode ? 'r' : '-';
	(*r)->perm[i++] = S_IWOTH & (*r)->file_stat.st_mode ? 'w' : '-';
	(*r)->perm[i++] = S_IXOTH & (*r)->file_stat.st_mode ? 'x' : '-';
	(*r)->perm[10] = '\0';
	make_other_perm(&(*r));
}
