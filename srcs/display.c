/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:38:36 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/27 09:00:42 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int ft_pchar(int c)
{
	write(2, &c, 1);
	return (c);
}

int verif_place(t_term_parameter *term)
{
	size_t size_max;

	size_max = term->nb_column * term->line;
	return (size_max >= term->select->size_lst);
}

void display_name(t_save_select *sv, int i, int j, int current)
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

void display_name_no_coor(t_save_select *sv, int current)
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
	//	tputs(tgetstr("cm", NULL), 1, ft_pchar);
}

void fill_screen(t_term_parameter *term)
{
	int i;
	size_t current_column;
	size_t sz_name;
	char blank[term->column];

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
		while (term->column > sz_name)
		{
			blank[i++] = ' ';
			++sz_name;
		}
		tputs(blank, 1, ft_pchar);
		term->select->current = term->select->current->next;
	}
	term->select->current = term->select->head;
}

void redisplay(t_term_parameter *term)
{
	calc_term(term);
	term->select->current = term->select->head;
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	fill_screen(term);
}

void del_column(char **keys, int *i, int *j, t_term_parameter *term)
{
	int next_exist;
	int index;
	t_select *current;

	index = -1;
	while (++index < (int)term->column)
		tputs(tgoto(keys[6], *j, *i), 1, ft_pchar);
	next_exist = del_select(term->select);
	current = term->select->current;
	redisplay(term);
	term->select->current = current;
	if (!next_exist)
	{
		next_exist = *j - (int)term->column;
		if (next_exist < 0)
		{
			next_exist = (term->nb_column * term->column) - term->column;
			if (*i > 0)
				*i -= 1;
		}
		*j = next_exist;
	}
	tputs(tgoto(keys[0], *j, *i), 1, ft_pchar);
	display_name(term->select, *i, *j, 1);
}
