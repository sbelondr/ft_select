/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:10:13 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 09:50:55 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_ls.h"

void	sv_move(t_read *r, t_save *sv, t_read *last)
{
	sv->list_last->next = r->next;
	r->next = sv->list;
	if (last)
		last->next = r;
	else
		sv->p_start->next = r;
}

void	move_sv(t_save **sv)
{
	t_read	*a;
	t_read	*b;

	a = (*sv)->list;
	b = (*sv)->list->next;
	if ((*sv)->list_last)
		(*sv)->list_last->next = b;
	else
		(*sv)->p_start->next = b;
	a->next = b->next;
	b->next = a;
}
