/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:47:29 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/28 09:19:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
 ** http://manpagesfr.free.fr/man/man3/termios.3.html
 ** http://www.cs.uleth.ca/~holzmann/C/system/ttyraw.c
 ** termios.truc |= (); -> active flag
 ** termios.truc &= ~(); -> desactive flag
 */

char	**init_keys_select(void)
{
	char	**keys;

	if (!(keys = (char**)malloc(sizeof(char*) * 9)))
		return (NULL);
	keys[0] = tgetstr("cm", NULL);
	keys[1] = tgetstr("cl", NULL);
	keys[2] = tgetstr("kd", NULL);
	keys[3] = tgetstr("ku", NULL);
	keys[4] = tgetstr("kl", NULL);
	keys[5] = tgetstr("kr", NULL);
	keys[6] = tgetstr("dc", NULL);
	keys[7] = tgetstr("ts", NULL);
	keys[8] = 0;
	return (keys);
}

void	return_value(t_term_parameter *term)
{
	char			*tmp;
	char			*src;
	t_select	*s;
	int				first;

	first = 1;
	src = ft_strdup("");
	tmp = NULL;
	s = term->select->head;
	while (s)
	{
		if (s->is_select)
		{
			if (first)
				first = 0;
			else
			{
				tmp = ft_strjoin(src, " ");
				ft_strdel(&src);
				src = tmp;
			}
			tmp = ft_strjoin(src, s->name);
			ft_strdel(&src);
			src = tmp;
		}
		s = s->next;
	}
	ft_putstr_fd(src, STDOUT_FILENO);
	ft_strdel(&src);
}

int		ft_select(t_save_select *sv, t_term_parameter *term)
{
	int		i;
	int		j;
	char	**keys;
	char	buf[3];

	keys = init_keys_select();
	tputs(keys[1], 1, ft_pchar);
	sv->current = sv->head;
	term->select->current = sv->head;
	fill_screen(sv, term);
	i = 0;
	j = 0;
	tputs(tgoto(keys[0], j, i), 1, ft_pchar);
	display_name(sv, i, j, 1);
	ft_bzero(buf, 3);
	while (read(0, buf, 3))
	{
		if ((buf[0] == 27 || buf[0] == 10 || buf[0] == 13) && buf[1] == 0)
			break ;
		else if (buf[0] == 32 && buf[1] == 0)
		{
			sv->current->is_select = sv->current->is_select ? 0 : 1;
			display_name(sv, i, j, 1);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51)
		{
			del_column(keys, &i, &j, term);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		{
			display_name(sv, i, j, 0);
			i -= 1;
			move_line(keys, &i, &j, term, 0);
			display_name(sv, i, j, 1);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		{
			display_name(sv, i, j, 0);
			i += 1;
			move_line(keys, &i, &j, term, 1);
			display_name(sv, i, j, 1);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		{
			if (term->select->current->next)
			{
				display_name(sv, i, j, 0);
				term->select->current = term->select->current->next;
				j += term->column;
				move_column(keys, &i, &j, term->column);
				display_name(sv, i, j, 1);
			}
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		{
			if (term->select->current->prev)
			{
				display_name(sv, i, j, 0);
				term->select->current = term->select->current->prev;
				j -= term->column;
				move_column(keys, &i, &j, term->column);
				display_name(sv, i, j, 1);
			}
		}
		ft_bzero(buf, 3);
	}
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	free(keys);
	if ((buf[0] == 13 || buf[0] == 10) && buf[1] == 0 && buf[2] == 0)
		return_value(term);
	reset_term(term);
	free_term(&term);
	return (0);
}

t_term_parameter	**get_term_parameter(t_term_parameter **term)
{
	static t_term_parameter	**t;

	if ((!t) && term)
		t = term;
	return (t);
}

int		main(int ac, char **av)
{
	t_term_parameter	*term;
	t_save_select			*sv;

	if (ac < 2)
		return (-1);
	sv = create_lst_select(av + 1);
	sv->current = sv->head;
	term = init_term(sv);
	get_term_parameter(&term);
	if (!verif_place(term))
	{
		ft_putstr_fd("Too many parameters compared to the size of the screen\n", STDERR_FILENO);
		reset_term(term);
		return (-1);
	}
	signals_select();
	ft_select(sv, term);
	return (0);
}
