/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_termcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:39:30 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/26 08:39:36 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	move_column(t_term_parameter *term, char **keys, int *i, int *j, size_t size_column)
{
	int			column;

	column = term->sz.ws_col;// tgetnum("co");
	column = column - (column % size_column);
	if (*j >= column)
	{
		++(*i);
		(*j) = 0;
	}
	else if (*j < 0)
	{
		if (*i > 0)
			--(*i);
		else
		{
			(*j) = 0;
			return ;
		}
		(*j) = column - size_column;
	}
	tputs(tgoto(keys[0], *j, *i), 1, ft_pchar);
}

void	move_line(char **keys, int *i, int *j, t_term_parameter *term, int top)
{
	int	place;
	int	value_column;

	value_column = (*j) > 0 ? *j / (int)term->column : 0;
	place = (term->nb_column * term->line_max) - term->select->size_lst;
	if (*i < 0)
	{
		*i = term->line_max - 1;
			++value_column;
		if (value_column > ((int)term->nb_column - place))
		{
			*i -= 1;
			int nb_test = ((int)term->nb_column - place) + ((int)term->nb_column - value_column);
			move_end_lst(term, nb_test);
		}
		else
		{
			int	calc = ((int)term->nb_column - place) - value_column;
			move_end_lst(term, calc);
		}
	}
	else if (*i >= (int)term->line_max)
	{
		move_head_lst(term, *j);
		*i = 0;
	}
	else if (*i == ((int)term->line_max - 1))
	{
		if (*j > 0)
		{
			if ((*j / (int)term->column) >= ((int)term->nb_column - place))
			{
				*i = 0;
				move_head_lst(term, *j);
			}
			else
				move_lst(term, top);
		}
		else
		{
			if (0 >= ((int)term->nb_column - place))
			{
				*i = 0;
				move_head_lst(term, *j);
			}
			else
				move_lst(term, top);
		}
	}
	else
		move_lst(term, top);
	tputs(tgoto(keys[0], *j, *i), 1, ft_pchar);
}
