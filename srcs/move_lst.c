/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:39:12 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/26 08:39:45 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	move_lst(t_term_parameter *term, int top)
{
	int	i;

	i = -1;
	while (++i < (int)term->nb_column)
	{
		if (top)
		{
			if (term->select->current->next)
				term->select->current = term->select->current->next;
			else
				break ;
		}
		else
		{
			if (term->select->current->prev)
				term->select->current = term->select->current->prev;
			else
				break ;
		}
	}
}

void	move_head_lst(t_term_parameter *term, int nb)
{
	int	i;

	i = -1;
	if (nb > 0)
		nb /= term->column;
	term->select->current = term->select->head;
	while (++i < nb)
	{
		if (term->select->current->next)
			term->select->current = term->select->current->next;
		else
			break ;
	}
}

void	move_end_lst(t_term_parameter *term, int nb)
{
	int	i;

	i = -1;
	term->select->current = term->select->end;
	while (++i < nb)
	{
		if (term->select->current->prev)
			term->select->current = term->select->current->prev;
		else
			break ;
	}
}
