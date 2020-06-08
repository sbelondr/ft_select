/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:47:29 by sbelondr          #+#    #+#             */
/*   Updated: 2020/06/08 16:48:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static char			**init_keys_select(void)
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

void				launch_select(t_term_parameter *term, char **keys)
{
	char buf[3];

	ft_bzero(buf, 3);
	while (read(0, buf, 3))
	{
		if ((buf[0] == 27 || buf[0] == 10 || buf[0] == 13) && buf[1] == 0)
			break ;
		else if (buf[0] == 32 && buf[1] == 0)
			act_space(term, term->coor, keys);
		else if ((buf[0] == 127 || buf[0] == 126) && buf[1] == 0)
		{
			if (!del_column(term, keys))
				act_end(keys, buf, term);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
			act_bottom(term, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
			act_top(term, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
			act_right(term, keys);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
			act_left(term, keys);
		ft_bzero(buf, 3);
	}
	act_end(keys, buf, term);
}

int					ft_select(t_term_parameter *term)
{
	char **keys;

	keys = init_keys_select();
	term->select->current = term->select->head;
	fill_screen(term);
	tputs(tgoto(keys[0], term->coor.x, term->coor.y), 1, ft_pchar);
	display_name(term->select, term->coor.y, term->coor.x, 1);
	launch_select(term, keys);
	return (0);
}

t_term_parameter	**get_term_parameter(t_term_parameter **term)
{
	static t_term_parameter **t;

	if ((!t) && term)
		t = term;
	return (t);
}

int					main(int ac, char **av)
{
	t_term_parameter	*term;
	t_save_select		*sv;

	if (ac < 2)
		return (-1);
	sv = create_lst_select(av + 1);
	sv->current = sv->head;
	term = init_term(sv);
	if (!term)
		exit(-1);
	get_term_parameter(&term);
	if (!verif_place(term))
	{
		ft_putstr_fd("Too small\n",
			STDERR_FILENO);
		reset_term(term);
		return (-1);
	}
	signals_select();
	ft_select(term);
	return (0);
}
