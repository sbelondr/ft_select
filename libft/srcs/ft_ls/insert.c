/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:49:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 10:47:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

void		recover_path(char (*path)[BUF_S], t_ls *ls, int index)
{
	ft_bzero(&(*path), BUF_S);
	ft_join(&(*path), ls->options[index], 0);
	((*path)[ft_strlen(*path) - 1] != '/') ? ft_join(&(*path), "/", 0) : 0;
	if (ls->options[index][0] == '/' && ft_cnt_chr(ls->options[index], '/') < 3)
		ft_join(&(*path), "/", 0);
	ft_join(&(*path), ls->read_file->d_name, 0);
}

int			insert_read(t_ls **ls, int index, t_save **sv)
{
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->read_file->d_name, (*ls)))
		return (0);
	if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->read_file->d_name);
	recover_path(&(r)->path, (*ls), index);
	if (stat(r->path, &(r)->file_stat) > 0)
		error_see();
	make_perm(&r, (*ls));
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
		r->pwuser = 0;
	((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL) ? error_see() : 0;
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(time_str, &r);
	(*ls)->total += add_total(&r);
	insert_sv(&(*sv), r);
	cnt_column(&(*ls), r);
	return (1);
}

int			insert_read_sl(t_ls **ls, int index)
{
	t_save	*sv;
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->options[index], (*ls)) ||
			!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->options[index]);
	ft_cpy_str(&(r->path), r->name);
	(lstat(r->name, &(r)->file_stat) > 0) ? error_see() : 0;
	make_perm(&r, (*ls));
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
		r->pwuser = 0;
	((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL) ? error_see() : 0;
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(time_str, &r);
	(*ls)->total += add_total(&r);
	sv = init_sv();
	insert_sv(&sv, r);
	check_permission(r) ? display_read((*ls), sv, -1) : error_permissions(r);
	delete_sv(&sv, 1);
	return (1);
}

int			insert_read_file(t_ls **ls, int index)
{
	t_save	*sv;
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->options[index], (*ls)) ||
			!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->options[index]);
	if (access_stat(&(*ls), &r, index))
		return (0);
	make_perm(&r, (*ls));
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
		r->pwuser = 0;
	((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL) ? error_see() : 0;
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(time_str, &r);
	(*ls)->total += add_total(&r);
	sv = init_sv();
	insert_sv(&sv, r);
	cnt_column(&(*ls), r);
	check_permission(r) ? display_read((*ls), sv, -1) : error_permissions(r);
	delete_sv(&sv, 1);
	return (1);
}
