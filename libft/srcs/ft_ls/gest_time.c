/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:35:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:49:50 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

void	hour_or_year(char **split, t_read **r)
{
	char	**split_time;
	time_t	t;
	int		i;
	int		verif;

	t = time(NULL);
	verif = ((t - (*r)->file_stat.st_mtime) < 15768000) ? 1 : 0;
	((t - (*r)->file_stat.st_mtime) < 0) ? verif = 0 : 0;
	if (verif == 1)
	{
		split_time = ft_strsplit(split[3], ':');
		ft_cpy_str(&(*r)->year_or_hours, split_time[0]);
		ft_join(&(*r)->year_or_hours, ":", 0);
		ft_join(&(*r)->year_or_hours, split_time[1], 0);
	}
	else
	{
		split_time = ft_strsplit(split[4], '\n');
		ft_cpy_str(&(*r)->year_or_hours, split_time[0]);
	}
	i = -1;
	while (split_time[++i])
		ft_strdel(&split_time[i]);
	free(split_time);
	split_time = NULL;
}

void	split_time(char *str, t_read **r)
{
	char	**split;
	int		i;

	split = ft_strsplit(str, ' ');
	ft_cpy_str(&(*r)->mois, split[1]);
	ft_cpy_str(&(*r)->jour, split[2]);
	hour_or_year(split, &(*r));
	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
}

int		sort_t(struct stat info_a, struct stat info_b)
{
	struct timespec	tm_a;
	struct timespec	tm_b;

	tm_a = info_a.st_mtimespec;
	tm_b = info_b.st_mtimespec;
	if (tm_a.tv_sec < tm_b.tv_sec)
		return (1);
	if (tm_a.tv_sec == tm_b.tv_sec)
		return (-1);
	return (0);
}
