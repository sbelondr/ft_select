/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:45:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 10:50:05 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_LS_H
#	define FT_LS_H

#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <uuid/uuid.h>
#include <time.h>
#include <sys/xattr.h>

struct dirent		*readdir(DIR *repertoire);

typedef struct		s_ls
{
	char			flags[10];
	DIR				*rep;
	long long		total;
	char			**options;
	struct dirent	*read_file;
	int				column[10];
}					t_ls;

typedef struct		s_read
{
	t_ls			*ls;
	char			*name;
	struct stat		file_stat;
	struct passwd	*pwuser;
	struct group	*grpname;
	char			path[BUF_S];
	char			perm[11];
	char			mois[BUF_S];
	char			jour[BUF_S];
	char			year_or_hours[BUF_S];
	char			symbolic_link[BUF_S];
	struct s_read	*next;
}					t_read;

typedef struct		s_save
{
	t_read			*p_start;
	t_read			*list;
	t_read			*list_last;
}					t_save;

/*
** ft_ls.c
*/

int					ft_ls(int ac, char **av);
int					first_sort_options(t_ls **ls, int len, int *srt_options);

/*
** init.c
*/

int					init_ls(t_ls **ls);
int					init_srt_options(t_ls **ls, int len);
int					remove_ls(t_ls **ls, int len);
void				ft_dirdel(DIR **check);

/*
** parcours.c
*/

int					open_file_options(t_ls **ls, int len, int *srt_options);
int					sort_options_is_exist(t_ls **ls, int index_option);

/*
** parser.c
*/

int					parser(int ac, char **flags, t_ls **ls);

/*
** error.c
*/

void				error_option(char c);
void				error_see(void);
void				error_rep(char *str);
void				error_permissions(t_read *r);

/*
** open.c
*/

int					open_ls(t_ls **ls, int index, int see_folder, int first);

/*
** insert.c
*/

int					insert_read(t_ls **ls, int index, t_save **sv);
int					insert_read_sl(t_ls **ls, int index);
int					insert_read_file(t_ls **ls, int index);

/*
** tools_insert.c
*/

int					verif_name(char *str, t_ls *ls);
long long			add_total(t_read **r);
void				cnt_column(t_ls **ls, t_read *r);
int					check_permission(t_read *r);
int					access_stat(t_ls **ls, t_read **r, int index);

/*
** permissions.c
*/

void				make_perm(t_read **r, t_ls *ls);

/*
** gest_time.c
*/

void				hour_or_year(char **split, t_read **r);
void				split_time(char *str, t_read **r);
int					sort_t(struct stat info_a, struct stat info_b);

/*
** list.c
*/

t_save				*init_sv(void);
void				insert_sv(t_save **sv, t_read *r);
void				next_sv(t_save *sv);
void				first_sv(t_save *sv);
size_t				size_sv(t_save *sv);

/*
** list_remove.c
*/

void				delete_sv(t_save **sv, int cnt);

/*
** display.c
*/

void				display_read(t_ls *ls, t_save *sv, int break_line);
void				verif_space_line(int nb_space);

/*
** display_l.c
*/

void				display_read_l(t_read *r, int is_s, t_ls *ls);

/*
** move.c
*/

void				sv_move(t_read *r, t_save *sv, t_read *last);
void				move_sv(t_save **sv);

/*
** sort.c
*/

void				ft_sort_ls(t_save **sv, t_ls **ls);

#	endif
