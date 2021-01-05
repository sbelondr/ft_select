/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:38:36 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/28 11:26:16 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

#include <stdio.h>

/*
** mr -> highlight
** me -> End all mode like so, us, mb, md, and mr
** us -> start underline
** ue -> stop underline
** cm -> cursor move column left to right
*/

void	display_name(t_save_select *sv, int i, int j, int current)
{
	if (sv->current->is_select)
		tputs(tgoto(tgetstr("mr", NULL), j, i), 0, ft_pchar);
	if (current)
		tputs(tgoto(tgetstr("us", NULL), j, i), 0, ft_pchar);
	tputs(sv->current->name, 1, ft_pchar);
	if (current)
		tputs(tgoto(tgetstr("ue", NULL), j, i), 1, ft_pchar);
	if (sv->current->is_select)
		tputs(tgoto(tgetstr("me", NULL), j, i), 1, ft_pchar);
	tputs(tgoto(tgetstr("cm", NULL), j, i), 1, ft_pchar);
}

void	display_name_no_coor(t_save_select *sv, int current)
{
	if (sv->current->is_select)
		tputs(tgetstr("mr", NULL), 0, ft_pchar);
	if (current)
		tputs(tgetstr("us", NULL), 0, ft_pchar);
	tputs(sv->current->name, 1, ft_pchar);
	if (current)
		tputs(tgetstr("ue", NULL), 1, ft_pchar);
	if (sv->current->is_select)
		tputs(tgetstr("me", NULL), 1, ft_pchar);
}

void	fill_screen(t_term_parameter *term)
{
	int		i;
	size_t	current_column;
	size_t	sz_name;
	char	blank[term->column];

	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	current_column = 0;
	while (term->select->current)
	{
		current_column += term->column;
		if (current_column > term->column_max)
		{
			current_column = term->column;
			tputs("\n", 1, ft_pchar);
		}
		sz_name = ft_strlen(term->select->current->name);
		display_name_no_coor(term->select, 0);
		ft_bzero(blank, term->column);
		i = 0;
		while (term->column > sz_name++)
			blank[i++] = ' ';
		tputs(blank, 1, ft_pchar);
		term->select->current = term->select->current->next;
	}
	term->select->current = term->select->head;
}

void	act_after_del(t_term_parameter *term, t_select *current,
	int next_exist, char **keys)
{
	redisplay(term);
	term->select->current = current;
	if ((!next_exist))
	{
		next_exist = term->coor.x - (int)term->column;
		if (next_exist < 0)
		{
			next_exist = (term->nb_column * term->column) - term->column;
			if (term->coor.y > 0)
				term->coor.y -= 1;
		}
		term->coor.x = next_exist;
	}
	tputs(tgoto(keys[0], term->coor.x, term->coor.y), 1, ft_pchar);
	display_name(term->select, term->coor.x, term->coor.y, 1);
	tputs(tgoto(keys[0], term->coor.x, term->coor.y), 1, ft_pchar);
}

int		del_column(t_term_parameter *term, char **keys)
{
	int			next_exist;
	int			index;
	t_select	*current;

	index = -1;
	while (++index < (int)term->column)
		tputs(tgoto(keys[6], term->coor.x, term->coor.y), 1, ft_pchar);
	next_exist = del_select(term->select);
	current = term->select->current;
	if (current)
		act_after_del(term, current, next_exist, keys);
	return (current ? 1 : 0);
}
