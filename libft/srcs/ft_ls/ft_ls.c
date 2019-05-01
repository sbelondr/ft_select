/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:21:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:49:37 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

int		sort_alph(char *path_a, char *path_b)
{
	int	result;

	result = ft_strcmp(path_a, path_b);
	if (result > 0)
		return (1);
	return (0);
}

int		info_search(char *path_a, char *path_b, t_ls *ls)
{
	int			verif;
	struct stat	info;
	struct stat	info_b;

	verif = -1;
	(stat(path_a, &info) == -1) ? verif = -2 : 0;
	if (stat(path_b, &info_b) == -1)
		verif = -2;
	if (verif == -1 && (S_ISREG(info.st_mode) || S_ISREG(info_b.st_mode)))
	{
		if (S_ISREG(info.st_mode) && S_ISDIR(info_b.st_mode))
			verif = 0;
		if (S_ISREG(info_b.st_mode) && S_ISDIR(info.st_mode))
			verif = 1;
	}
	if (verif == -1 || verif == -2)
	{
		if (verif == -1 && ft_strchr_exist(ls->flags, 't'))
			verif = sort_t(info, info_b);
		if (verif == -1 || verif == -2)
			verif = sort_alph(path_a, path_b);
	}
	if (ft_strchr_exist(ls->flags, 'r'))
		verif = (verif == 0) ? 1 : 0;
	return (verif);
}

/*
** http://manpagesfr.free.fr/man/man2/stat.2.html
*/

int		sort_options(t_ls **ls, int len, int *srt_options)
{
	int		i;
	int		k;
	int		stock;

	k = -1;
	while (++k < len)
	{
		i = -1;
		while (++i < len - 1)
		{
			if (srt_options[i] != -1)
			{
				if (srt_options[i + 1] == -1 ||
						info_search((*ls)->options[srt_options[i]],
							(*ls)->options[srt_options[i + 1]], (*ls)))
				{
					stock = srt_options[i];
					srt_options[i] = srt_options[i + 1];
					srt_options[i + 1] = stock;
				}
			}
		}
	}
	stock = open_file_options(&(*ls), len, srt_options);
	return (stock);
}

int		first_sort_options(t_ls **ls, int len, int *srt_options)
{
	int	i;
	int	k;
	int	stock;

	k = -1;
	while (++k < len)
	{
		i = -1;
		while (++i < len - 1)
		{
			if (ft_strcmp((*ls)->options[srt_options[i]],
						(*ls)->options[srt_options[i + 1]]) > 0)
			{
				stock = srt_options[i];
				srt_options[i] = srt_options[i + 1];
				srt_options[i + 1] = stock;
			}
		}
	}
	i = -1;
	while (++i < len)
		if (sort_options_is_exist(&(*ls), srt_options[i]) == -1)
			srt_options[i] = -1;
	stock = sort_options(&(*ls), len, srt_options);
	return (stock);
}

int		ft_ls(int ac, char **av)
{
	t_ls	*ls;
	int		len;
	int		check;
	int		verif;

	verif = 0;
	if (!av)
		return (-1);
	if (init_ls(&ls) == -1)
		return (-1);
	len = parser(ac, av, &ls);
	check = (len < 1) ? 1 : len;
	verif = init_srt_options(&ls, check);
	if (remove_ls(&ls, len) == -1)
		return (-1);
	return (verif);
}
