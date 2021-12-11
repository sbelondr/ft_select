/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:39:51 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 15:33:49 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
** init termcap
*/

int					init_termcap(t_term_parameter *term)
{
	char	*env;

	if (tcgetattr(term->fd_in, &(term->base_term)) < 0)
		return (0);
	if (ft_tty_raw(term->base_term, term->fd_in) == -1)
	{
		ft_dprintf(2, "Error: raw doesn't work!\n");
		return (0);
	}
	env = getenv("TERM");
	if ((!env) || ft_strequ(env, "") || tgetent(0, env) == -1)
	{
		ft_dprintf(2, "Error: tgetent doesn't work!\n");
		return (0);
	}
	return (1);
}

size_t				ft_size_lst_select(t_save_select *sv)
{
	t_select	*s;
	size_t		sz;

	s = sv->head;
	sz = 0;
	while (s)
	{
		++sz;
		s = s->next;
	}
	return (sz);
}

/*
** calc column and line size
*/

void				calc_term(t_term_parameter *term)
{
	size_t			size_lst;
	struct winsize	sz;
	int				column;

	ioctl(0, TIOCGWINSZ, &sz);
	term->sz = sz;
	size_lst = ft_size_lst_select(term->select);
	term->column = term->select->max_size + 2;
	term->column_max_last_line = 0;
	column = sz.ws_col;
	column = column - (ft_modulo(column, term->column));
	term->column_max = column;
	term->line = sz.ws_row;
	term->nb_column = ft_division(term->column_max, term->column);
	term->line_max = ft_division(size_lst, term->nb_column);
	if (ft_modulo(size_lst, term->nb_column) > 0)
		term->line_max += 1;
}

/*
** init structure
*/

t_term_parameter	*init_term(t_save_select *s)
{
	t_term_parameter	*term;

	if (!(term = (t_term_parameter*)malloc(sizeof(t_term_parameter) * 1)))
		return (NULL);
	term->select = s;
	term->coor.y = 0;
	term->coor.x = 0;
	term->fd_in = STDIN_FILENO;
	term->block_signal = 0;
	if (!init_termcap(term))
	{
		reset_term(&term, 1);
		free(term);
		term = NULL;
		return (NULL);
	}
	calc_term(term);
	tputs(tgoto(tgetstr("vi", NULL), 0, 0), 1, ft_pchar);
	return (term);
}

/*
** restore default terminal parameter and free term
*/

int					reset_term(t_term_parameter **term, int is_free)
{
	tputs(tgoto(tgetstr("ve", NULL), 0, 0), 1, ft_pchar);
	if (tty_reset((*term)->base_term, (*term)->fd_in) == -1)
	{
		free_term(term);
		ft_dprintf(2, "Error: reset raw doesn't work!\n");
		return (-1);
	}
	if (is_free)
		free_term(term);
	return (0);
}
