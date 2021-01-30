/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_termcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:39:30 by sbelondr          #+#    #+#             */
/*   Updated: 2021/01/30 10:31:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <stdio.h>

void	move_column(t_term_parameter *term, char **keys)
{
	if (term->coor.x >= (int)term->column_max)
	{
		++term->coor.y;
		term->coor.x = 0;
	}
	else if (term->coor.x < 0)
	{
		if (term->coor.y > 0)
			--term->coor.y;
		else
		{
			term->coor.x = 0;
			return ;
		}
		term->coor.x = term->column_max - term->column;
	}
	tputs(tgoto(keys[0], term->coor.x, term->coor.y), 1, ft_pchar);
}

void	move_line_up(t_term_parameter *term, int place)
{
	int	value_column;
	int	calc;

	value_column = (term->coor.x) > 0 ?
		ft_division(term->coor.x, (int)term->column) : 0;
	term->coor.y = term->line_max - 1;
	++value_column;
	if (value_column > ((int)term->nb_column - place))
	{
		term->coor.y -= 1;
		calc = ((int)term->nb_column - place)
			+ ((int)term->nb_column - value_column);
		move_end_lst(term, calc);
	}
	else
	{
		calc = ((int)term->nb_column - place) - value_column;
		move_end_lst(term, calc);
	}
}

void	verif_move_line_down(t_term_parameter *term, int place, int top)
{
	if (term->coor.x > 0)
	{
		if ((ft_division(term->coor.x, (int)term->column))
			>= ((int)term->nb_column - place))
		{
			term->coor.y = 0;
			move_head_lst(term, term->coor.x);
		}
		else
			move_lst(term, top);
	}
	else
	{
		if (0 >= ((int)term->nb_column - place))
		{
			term->coor.y = 0;
			move_head_lst(term, term->coor.x);
		}
		else
			move_lst(term, top);
	}
}

void	move_line(char **keys, t_term_parameter *term, int top)
{
	int	place;

	place = (term->nb_column * term->line_max) - term->select->size_lst;
	if (term->coor.y < 0)
		move_line_up(term, place);
	else if (term->coor.y >= (int)term->line_max)
	{
		move_head_lst(term, term->coor.x);
		term->coor.y = 0;
	}
	else if (term->coor.y == ((int)term->line_max - 1))
		verif_move_line_down(term, place, top);
	else
		move_lst(term, top);
	tputs(tgoto(keys[0], term->coor.x, term->coor.y), 1, ft_pchar);
}
