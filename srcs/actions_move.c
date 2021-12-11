/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:15:40 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 15:56:05 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	act_top(t_term_parameter *term, char **keys)
{
	display_name(term->select, term->coor.y, term->coor.x, 0);
	term->coor.y += 1;
	move_line(keys, term, 1);
	display_name(term->select, term->coor.y, term->coor.x, 1);
}

void	act_bottom(t_term_parameter *term, char **keys)
{
	display_name(term->select, term->coor.y, term->coor.x, 0);
	term->coor.y -= 1;
	move_line(keys, term, 0);
	display_name(term->select, term->coor.y, term->coor.x, 1);
}

void	act_right(t_term_parameter *term, char **keys)
{
	if (term->select->current->next)
	{
		display_name(term->select, term->coor.y, term->coor.x, 0);
		term->select->current = term->select->current->next;
		term->coor.x += term->column;
		move_column(term, keys);
		display_name(term->select, term->coor.y, term->coor.x, 1);
	}
}

void	act_left(t_term_parameter *term, char **keys)
{
	if (term->select->current->prev)
	{
		display_name(term->select, term->coor.y, term->coor.x, 0);
		term->select->current = term->select->current->prev;
		term->coor.x -= term->column;
		move_column(term, keys);
		display_name(term->select, term->coor.y, term->coor.x, 1);
	}
}
