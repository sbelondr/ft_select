/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:47:29 by sbelondr          #+#    #+#             */
/*   Updated: 2020-04-25 11:55:11 by sbelondr         ###   ########.fr       */ 
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
 ** http://manpagesfr.free.fr/man/man3/termios.3.html
 ** http://www.cs.uleth.ca/~holzmann/C/system/ttyraw.c
 ** termios.truc |= (); -> active flag
 ** termios.truc &= ~(); -> desactive flag
 */

size_t	ft_size_lst_select(t_save_select *sv)
{
	t_select	*s;
	size_t		sz;

	s = sv->head;
	sz = 0;
	while (s)
	{
		++sz;
		s = s->next;
	}
	return (sz);
}

int		ft_tty_raw(struct termios base_term, int fd_in)
{
	struct termios	term_raw;


	term_raw = base_term;
//	term_raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
//			| INLCR | IGNCR | IXON);
//	term_raw.c_oflag &= ~OPOST;
//	term_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
//	term_raw.c_cflag &= ~(CSIZE | PARENB);
//	term_raw.c_cflag |= CS8;
//	term_raw.c_cc[VMIN] = 1;
//	term_raw.c_cc[VTIME] = 0;


	   term_raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	//term_raw.c_oflag &= ~(OPOST);
	term_raw.c_cflag &= ~(CS8);
	term_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);// | ISIG);
	term_raw.c_cc[VMIN] = 1;
	term_raw.c_cc[VTIME] = 0;
	//if (tcsetattr(fd_in, TCSANOW, &term_raw) < 0)
	if (tcsetattr(fd_in, TCSAFLUSH, &term_raw) < 0)
		return (-1);
	return (0);
}

int		tty_reset(struct termios base_term, int fd_in)
{
	//if (tcsetattr(fd_in, TCSANOW, &base_term) < 0)
	if (tcsetattr(fd_in, TCSAFLUSH, &base_term) < 0)
		return (-1);
	return (0);
}

int	ft_pchar(int c)
{
	write(1, &c, 1);
	return (c);
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
		tputs(sv->current->name, 1, ft_pchar);
		while (term->column > sz_name)
		{
			tputs(" ", 1, ft_pchar);
			++sz_name;
		}
		sv->current = sv->current->next;
	}
	sv->current = sv->head;
}

void	move_column(char **keys, int *i, int *j, size_t size_column)
{
	int			column;

	column = tgetnum("co");
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

void	move_line(char **keys, int *i, int *j, t_term_parameter *term, int top)
{
	int	place;
	int	value_column;

	value_column = (*j) > 0 ? *j / (int)term->column : 0;
	place = (term->nb_column * term->line_max) - term->select->size_lst;
	if (*i < 0)
	{
		*i = term->line_max - 1;
			if (value_column >= ((int)term->nb_column - place))
			{
				++value_column;
				*i -= 1;
				int nb_test = ((int)term->nb_column - place) + ((int)term->nb_column - value_column);
				move_end_lst(term, nb_test);
			}
			else
			{
				int	calc = (int)term->nb_column - (((int)term->nb_column - place) + value_column);
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

char	**init_keys_select(void)
{
	char	**keys;

	if (!(keys = (char**)malloc(sizeof(char*) * 9)))
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

void	del_column(char **keys, int i, int j, t_term_parameter *term)
{
	int	index;

	index = -1;
	while (++index < (int)term->column)
		tputs(tgoto(keys[6], j, i), 1, ft_pchar);
}

char	*test(t_save_select *sv, t_term_parameter *term)
{
	int		i;
	int		j;
	char	**keys;
	char	*final;
	char	buf[3];

	keys = init_keys_select();
	tputs(keys[1], 1, ft_pchar);
	fill_screen(sv, term);
	i = 0;
	j = 0;
	tputs(tgoto(keys[0], 0, i), 1, ft_pchar);
	ft_bzero(buf, 3);
	while (read(0, buf, 3))
	{
		if ((buf[0] == 27 || buf[0] == 10) && buf[1] == 0)
			break ;
		else if (buf[0] == 32 && buf[1] == 0)
		{
			tputs(tgoto(tgetstr("so", NULL), j, i), 1, ft_pchar);
			tputs(tgoto(tgetstr("sa", NULL), j, i), 1, ft_pchar);
			tputs(sv->current->name, 1, ft_pchar);
			tputs(tgoto(tgetstr("se", NULL), j, i), 1, ft_pchar);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51)
		{
			del_column(keys, i, j, term);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		{
			i -= 1;
			move_line(keys, &i, &j, term, 0);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		{
			i += 1;
			move_line(keys, &i, &j, term, 1);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		{
			if (term->select->current->next)
			{
				term->select->current = term->select->current->next;
				j += term->column;
				move_column(keys, &i, &j, term->column);
			}
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		{
			if (term->select->current->prev)
			{
				term->select->current = term->select->current->prev;
				j -= term->column;
				move_column(keys, &i, &j, term->column);
			}
		}
		ft_bzero(buf, 3);
	}
	final = NULL;
	return (final);	
}

int							init_termcap(t_term_parameter *term)
{
	char							*env;
	
	if (tcgetattr(term->fd_in, &(term->base_term)) < 0)
		return (0);
	if (ft_tty_raw(term->base_term, term->fd_in) == -1)
	{
		ft_dprintf(2, "Error: raw doesn't work!\n");
		return (0);
	}
	env = getenv("TERM");
	if ((!env) || tgetent(0, env) == -1)
	{
		ft_dprintf(2, "Error: tgetent doesn't work!\n");
		return (0);
	}
	return (1);
}

t_term_parameter	*init_term(t_save_select *s)
{
	t_term_parameter	*term;
	int								column;
	size_t						size_lst;

	if (!(term = (t_term_parameter*)malloc(sizeof(t_term_parameter) * 1)))
		return (NULL);
	size_lst = ft_size_lst_select(s);
	term->column = s->max_size + 2;
	term->column_max_last_line = 0;
	term->select = s;
	term->fd_in = STDIN_FILENO;
	if (!init_termcap(term))
		return (NULL);
	term->line = tgetnum("li");
	column = tgetnum("co");
	column = column - (column % term->column);
	term->column_max = column;
	term->nb_column = term->column_max / term->column;
	term->line_max = size_lst / term->nb_column;
	if ((size_lst % term->nb_column) > 0)
		term->line_max += 1;
	return (term);
}

int	reset_term(t_term_parameter *term)
{
	if (tty_reset(term->base_term, term->fd_in) == -1)
	{
		ft_dprintf(2, "Error: reset raw doesn't work!\n");
		return (-1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_term_parameter	*term;
	t_save_select			*sv;
	char							*final;

	if (ac < 2)
		return (-1);
	sv = create_lst_select(av + 1);
	sv->current = sv->head;
	term = init_term(sv);
	final = test(sv, term);
	ft_putstr(final);
	reset_term(term);
	return (0);
}
