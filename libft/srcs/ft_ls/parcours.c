/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcours.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:18:19 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:51:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

int		parcours(t_ls **ls, int len, int *srt_options, int check)
{
	int	i;
	int	verif;

	verif = 0;
	if (len == 1 && srt_options[0] != -1)
		verif = open_ls(&(*ls), 0, 0, 0);
	else
	{
		i = -1;
		while (++i < len)
		{
			if (srt_options[i] != -1)
				verif = open_ls(&(*ls), srt_options[i], i + 1, check++);
			else
				verif = 0;
		}
	}
	return (verif);
}

int		parcours_sl(t_ls **ls, int len, int *srt_options, int check)
{
	int			i;
	int			end;
	int			index;
	int			verif_stat;
	struct stat	verif;

	i = -1;
	while (++i < len)
	{
		index = srt_options[i];
		if (index != -1)
		{
			verif_stat = lstat((*ls)->options[index], &verif);
			end = ft_strlen((*ls)->options[index]) - 1;
			if (verif_stat >= 0 && (*ls)->options[index][0] == '/' &&
					(*ls)->options[index][end] != '/' && S_ISLNK(verif.st_mode))
			{
				insert_read_sl(&(*ls), index);
				check++;
				srt_options[i] = -1;
			}
		}
	}
	i = parcours(&(*ls), len, srt_options, check);
	return (i);
}

int		sort_options_is_exist(t_ls **ls, int index_option)
{
	t_read	*r;
	DIR		*check;

	check = NULL;
	if (index_option != -1 &&
			(check = opendir((*ls)->options[index_option])) == NULL)
	{
		if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
			return (0);
		if (stat((*ls)->options[index_option], &(r)->file_stat) < 0)
		{
			if (lstat((*ls)->options[index_option], &(r)->file_stat) < 0)
			{
				error_rep((*ls)->options[index_option]);
				free(r);
				r = NULL;
				return (-1);
			}
		}
		free(r);
		r = NULL;
	}
	else if (check != NULL)
		ft_dirdel(&check);
	return (1);
}

int		is_file(t_ls **ls, t_read **r, int *srt_options, int i)
{
	if (!(*r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	if (stat((*ls)->options[srt_options[i]], &(*r)->file_stat) >= 0 ||
			lstat((*ls)->options[srt_options[i]], &(*r)->file_stat) >= 0)
	{
		insert_read_file(&(*ls), srt_options[i]);
		free(*r);
		*r = NULL;
		return (1);
	}
	free(*r);
	*r = NULL;
	return (0);
}

int		open_file_options(t_ls **ls, int len, int *srt_options)
{
	int		i;
	int		verif;
	t_read	*r;
	DIR		*check;

	i = -1;
	verif = 0;
	while (++i < len)
	{
		if (srt_options[i] != -1 &&
				(check = opendir((*ls)->options[srt_options[i]])) == NULL)
		{
			if (is_file(&(*ls), &r, srt_options, i))
			{
				srt_options[i] = -1;
				verif++;
			}
		}
		else if (srt_options[i] != -1 && check != NULL)
			ft_dirdel(&check);
	}
	verif = parcours_sl(&(*ls), len, srt_options, verif);
	return (verif);
}
