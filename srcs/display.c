/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:38:36 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/26 09:51:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_pchar(int c)
{
	write(1, &c, 1);
	return (c);
}

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

void	fill_screen(t_save_select *sv, t_term_parameter *term)
{
	size_t	current_column;
	size_t	sz_name;

	current_column = 0;
	while (sv->current)
	{
		current_column += term->column;
		if (current_column > term->column_max)
		{
			current_column = term->column;
			tputs("\n", 1, ft_pchar);
		}
		sz_name = ft_strlen(sv->current->name);
		tputs(tgetstr("us", NULL), 0, ft_pchar);
		tputs(sv->current->name, 1, ft_pchar);
		tputs(tgetstr("ue", NULL), 0, ft_pchar);
		while (term->column > sz_name)
		{
			tputs(" ", 1, ft_pchar);
			++sz_name;
		}
		sv->current = sv->current->next;
	}
	sv->current = sv->head;
}

/*
void	fill_screen(t_save_select *sv, t_term_parameter *term)
{
	int			i;
	int			j;
	size_t	current_column;

	i = 0;
	j = 0;
	current_column = 0;
//	tputs(tgoto(keys[0], j, i), 1, ft_pchar);
	while (sv->current)
	{
		current_column += term->column;
		if (current_column > term->column_max)
		{
			j = 0;
			++i;
			current_column = term->column;
		}
		dprintf(5, "%s - %d - %d\n", sv->current->name, i, j);
		display_name(sv, i, j, 0);
		j += term->column;
		sv->current = sv->current->next;
	}
	sv->current = sv->head;
}
*/

void	del_column(char **keys, int i, int j, t_term_parameter *term)
{
	int	index;
	t_select	*current;

	index = -1;
	while (++index < (int)term->column)
		tputs(tgoto(keys[6], j, i), 1, ft_pchar);
	del_select(term->select);
	current = term->select->current;
	calc_term(term);
	term->select->current = term->select->head;
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	fill_screen(term->select, term);
	term->select->current = current;
	tputs(tgoto(keys[0], j, i), 1, ft_pchar);
	display_name(term->select, i, j, 1);
}
