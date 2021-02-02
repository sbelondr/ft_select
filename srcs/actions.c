/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:15:30 by sbelondr          #+#    #+#             */
/*   Updated: 2021/02/01 09:32:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void				act_space(t_term_parameter *term, t_pos coor, char **keys)
{
	term->select->current->is_select =
			term->select->current->is_select ? 0 : 1;
	display_name(term->select, coor.y, coor.x, 1);
	act_right(term, keys);
}

void				act_end(char **keys, char buf[3], t_term_parameter *term)
{
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	free(keys);
	if ((buf[0] == 13 || buf[0] == 10) && buf[1] == 0 && buf[2] == 0)
		return_value(term);
	reset_term(&term, 1);
	exit(0);
}
