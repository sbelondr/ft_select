/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 09:38:13 by sbelondr          #+#    #+#             */
/*   Updated: 2023/03/11 14:34:44 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termcap.h>
# include <termios.h>
# include <stdio.h>

typedef struct s_pos
{
	int		x;
	int		y;
}					t_pos;

typedef struct s_select
{
	char			*name;
	int				is_select;
	t_pos			pos;
	struct s_select	*next;
	struct s_select	*prev;
}					t_select;

typedef struct s_save_select
{
	t_select	*head;
	t_select	*current;
	t_select	*end;
	size_t		max_size;
	size_t		size_lst;
}					t_save_select;

typedef struct s_term_parameter
{
	size_t			column;
	size_t			nb_column;
	size_t			column_max;
	size_t			line;
	size_t			line_max;
	size_t			column_max_last_line;
	t_save_select	*select;
	struct termios	base_term;
	int				fd_in;
	t_pos			coor;
	struct winsize	sz;
	size_t			block_signal;
}					t_term_parameter;

t_term_parameter	**get_term_parameter(t_term_parameter **term);
int					ft_select(t_term_parameter *term);
void				manage_screen_small_start(t_term_parameter *term);

/*
** lst_select.c
*/

t_save_select		*create_lst_select(char **src);
int					del_select(t_save_select *s);
t_select			*init_select(char *str);

/*
** term.c
*/

void				calc_term(t_term_parameter *term);
t_term_parameter	*init_term(t_save_select *s);
int					reset_term(t_term_parameter **term, int is_free);

/*
** tty.c
*/

int					ft_tty_raw(struct termios term, int fd_in);
int					tty_reset(struct termios base_term, int fd_in);

/*
** display.c
*/

void				fill_screen(t_term_parameter *term);
void				display_name(t_save_select *sv, int i, int j, int current);
int					del_column(t_term_parameter *term, char **keys);

/*
** move_lst.c
*/

void				move_lst(t_term_parameter *term, int top);
void				move_head_lst(t_term_parameter *term, int nb);
void				move_end_lst(t_term_parameter *term, int nb);

/*
** move_termcat.c
*/

void				move_column(t_term_parameter *ter, char **keys);
void				move_line(char **keys, t_term_parameter *term, int top);

/*
** free.c
*/

void				free_term(t_term_parameter **term);
void				free_select(t_select **s);

/*
** signals.c
*/

void				signals_select(void);
void				sig_action(int sig);

/*
** reset_term.c
*/

void				ft_reset_term(t_term_parameter **term);

/*
** tools.c
*/

void				redisplay(t_term_parameter *term);
int					ft_pchar(int c);
int					verif_place(t_term_parameter *term);
void				return_value(t_term_parameter *term);

/*
** actions.c
*/

void				act_space(t_term_parameter *term, \
		t_pos coor, char **keys);
void				act_end(char **keys, char buf[3], \
		t_term_parameter *term);

/*
** actions_move.c
*/

void				act_top(t_term_parameter *term, char **keys);
void				act_bottom(t_term_parameter *term, char **keys);
void				act_right(t_term_parameter *term, char **keys);
void				act_left(t_term_parameter *term, char **keys);

/*
** manage_arg.c
*/

int					check_argv(char **av);
t_select			*edit_lst_select(t_select *select, char **src, int i);
t_save_select		*clean_lst(t_save_select *sv, t_select *select);

#	endif
