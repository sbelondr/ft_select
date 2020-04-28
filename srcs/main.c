/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:47:29 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/28 09:19:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
 ** http://manpagesfr.free.fr/man/man3/termios.3.html
 ** http://www.cs.uleth.ca/~holzmann/C/system/ttyraw.c
 ** termios.truc |= (); -> active flag
 ** termios.truc &= ~(); -> desactive flag
 */
char **init_keys_select(void)
{
	char **keys;

	if (!(keys = (char **)malloc(sizeof(char *) * 9)))
		return (NULL);
	keys[0] = tgetstr("cm", NULL);
	keys[1] = tgetstr("cl", NULL);
	keys[2] = tgetstr("kd", NULL);
	keys[3] = tgetstr("ku", NULL);
	keys[4] = tgetstr("kl", NULL);
	keys[5] = tgetstr("kr", NULL);
	keys[6] = tgetstr("dc", NULL);
	keys[7] = tgetstr("ts", NULL);
	keys[8] = 0;
	return (keys);
}

char *get_final_value(t_select *s)
{
	char *tmp;
	char *src;
	int first;

	first = 1;
	src = ft_strdup("");
	while (s)
	{
		if (s->is_select)
		{
			if (first)
				first = 0;
			else
			{
				tmp = ft_strjoin(src, " ");
				ft_strdel(&src);
				src = tmp;
			}
			tmp = ft_strjoin(src, s->name);
			ft_strdel(&src);
			src = tmp;
		}
		s = s->next;
	}
	return (src);
}

void return_value(t_term_parameter *term)
{
	t_select *s;
	char *src;

	s = term->select->head;
	src = get_final_value(s);
	ft_putstr_fd(src, STDOUT_FILENO);
	ft_strdel(&src);
}

void act_top(t_term_parameter *term, char **keys)
{
	display_name(term->select, term->coor.y, term->coor.x, 0);
	term->coor.y += 1;
	move_line(keys, &(term->coor.y), &(term->coor.x), term, 1);
	display_name(term->select, term->coor.y, term->coor.x, 1);
}

void act_bottom(t_term_parameter *term, char **keys)
{
	display_name(term->select, term->coor.y, term->coor.x, 0);
	term->coor.y -= 1;
	move_line(keys, &(term->coor.y), &(term->coor.x), term, 0);
	display_name(term->select, term->coor.y, term->coor.x, 1);
}

void act_left(t_term_parameter *term, char **keys)
{
	if (term->select->current->next)
	{
		display_name(term->select, term->coor.y, term->coor.x, 0);
		term->select->current = term->select->current->next;
		term->coor.x += term->column;
		move_column(term, keys, &(term->coor.y), &(term->coor.x), term->column);
		display_name(term->select, term->coor.y, term->coor.x, 1);
	}
}

void act_right(t_term_parameter *term, char **keys)
{
	if (term->select->current->prev)
	{
		display_name(term->select, term->coor.y, term->coor.x, 0);
		term->select->current = term->select->current->prev;
		term->coor.x -= term->column;
		move_column(term, keys, &(term->coor.y), &(term->coor.x), term->column);
		display_name(term->select, term->coor.y, term->coor.x, 1);
	}
}

void act_space(t_term_parameter *term, t_pos coor, char **keys)
{
	term->select->current->is_select =
			term->select->current->is_select ? 0 : 1;
	display_name(term->select, coor.y, coor.x, 1);
	act_left(term, keys);
}

void act_end(char **keys, char buf[3], t_term_parameter *term)
{
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	free(keys);
	if ((buf[0] == 13 || buf[0] == 10) && buf[1] == 0 && buf[2] == 0)
		return_value(term);
	reset_term(term);
	free_term(&term);
}

int ft_select(t_term_parameter *term)
{
	char **keys;
	char buf[3];

	keys = init_keys_select();
	term->select->current = term->select->head;
	fill_screen(term);
	tputs(tgoto(keys[0], term->coor.x, term->coor.y), 1, ft_pchar);
	display_name(term->select, term->coor.y, term->coor.x, 1);
	ft_bzero(buf, 3);
	while (read(0, buf, 3))
	{
		if ((buf[0] == 27 || buf[0] == 10 || buf[0] == 13) && buf[1] == 0)
			break;
		else if (buf[0] == 32 && buf[1] == 0)
			act_space(term, term->coor, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51)
			del_column(keys, &(term->coor.y), &(term->coor.x), term);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
			act_bottom(term, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
			act_top(term, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
			act_left(term, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
			act_right(term, keys);
		ft_bzero(buf, 3);
	}
	act_end(keys, buf, term);
	return (0);
}

t_term_parameter **get_term_parameter(t_term_parameter **term)
{
	static t_term_parameter **t;

	if ((!t) && term)
		t = term;
	return (t);
}

int main(int ac, char **av)
{
	t_term_parameter *term;
	t_save_select *sv;

	if (ac < 2)
		return (-1);
	sv = create_lst_select(av + 1);
	sv->current = sv->head;
	term = init_term(sv);
	get_term_parameter(&term);
	if (!verif_place(term))
	{
		ft_putstr_fd("Too many parameters compared to the size of the screen\n", STDERR_FILENO);
		reset_term(term);
		return (-1);
	}
	signals_select();
	ft_select(term);
	return (0);
}
