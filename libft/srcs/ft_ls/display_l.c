/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:03:23 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:49:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

int		majmin_read(t_read *r, t_ls *ls)
{
	int	major;
	int	minor;
	int	cnt;

	major = major(r->file_stat.st_rdev);
	minor = minor(r->file_stat.st_rdev);
	cnt = ls->column[8] - ft_numlen(major);
	verif_space_line(cnt);
	ft_printf("%d,", major);
	cnt = ls->column[9] - ft_numlen(minor);
	verif_space_line(cnt);
	ft_printf("%d", minor);
	return (cnt);
}

void	display_user(t_read *r, t_ls *ls)
{
	char	*str;

	if (r->pwuser)
	{
		str = ft_strdup(r->pwuser->pw_name);
		ft_putstr(str);
		verif_space_line(ls->column[2] - (int)ft_strlen(str));
		ft_strdel(&str);
	}
	else
	{
		ft_printf("%u", r->file_stat.st_uid);
		verif_space_line(ls->column[2] - ft_numlen(r->file_stat.st_uid));
	}
}

void	display_size(t_read *r, t_ls *ls)
{
	int	len;

	if (r->perm[0] != 'b' && r->perm[0] != 'c')
	{
		if (ls->column[8] > 0 || ls->column[9] > 0)
			len = (ls->column[8] + ls->column[9] + 2);
		else
			len = ls->column[4];
		verif_space_line(len - ft_numlen(r->file_stat.st_size));
		ft_putnbr(r->file_stat.st_size);
	}
	else
		len = majmin_read(r, ls);
}

void	display_name(t_read *r)
{
	if (r->perm[0] == 'd')
		ft_putstr(r->name);
	else
		ft_putstr(r->name);
	if (r->perm[0] == 'l')
		if (r->symbolic_link[0] != '\0')
			ft_printf(" -> %s", r->symbolic_link);
}

void	display_read_l(t_read *r, int is_s, t_ls *ls)
{
	char	*str;

	if (is_s)
		ft_printf("%d\t", r->file_stat.st_blocks);
	ft_putstr(r->perm);
	ft_putchar(' ');
	verif_space_line(ls->column[1] - ft_numlen(r->file_stat.st_nlink));
	ft_putnbr(r->file_stat.st_nlink);
	ft_putchar(' ');
	display_user(r, ls);
	str = ft_strdup(r->grpname->gr_name);
	ft_putstr(str);
	verif_space_line(ls->column[3] - (int)ft_strlen(str));
	ft_strdel(&str);
	display_size(r, ls);
	verif_space_line(ls->column[5] - ft_strlen(r->mois));
	ft_putstr(r->mois);
	verif_space_line(ls->column[6] - ft_strlen(r->jour));
	ft_putstr(r->jour);
	verif_space_line(ls->column[7] - ft_strlen(r->year_or_hours));
	ft_putstr(r->year_or_hours);
	ft_putchar(' ');
	display_name(r);
	ft_putchar('\n');
}
