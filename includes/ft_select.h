/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 09:38:13 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/27 13:24:19 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_SELECT_H
#	define FT_SELECT_H

#include "../libft/includes/libft.h"
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

typedef struct		s_pos
{
	int	x;
	int	y;
}									t_pos;

typedef struct		s_select
{
	char						*name;
	int							is_select;
	t_pos						pos;
	struct s_select	*next;
	struct s_select	*prev;
}									t_select;

typedef struct		s_save_select
{
	t_select	*head;
	t_select	*current;
	t_select	*end;
	size_t		max_size;
	size_t		size_lst;
}									t_save_select;

typedef struct		s_term_parameter
{
	size_t					column;
	size_t					nb_column;
	size_t					column_max;
	size_t					line;
	size_t					line_max;
	size_t					column_max_last_line;
	t_save_select		*select;
	struct termios	base_term;
	int							fd_in;
}									t_term_parameter;

t_term_parameter	**get_term_parameter(t_term_parameter **term);
int						   ft_select(t_save_select *sv, t_term_parameter *term);

/*
** lst_select.c
*/
t_save_select			*create_lst_select(char **src);
int								del_select(t_save_select *s);

/*
** term.c
*/
void							calc_term(t_term_parameter *term);
t_term_parameter	*init_term(t_save_select *s);
int								reset_term(t_term_parameter *term);

/*
** tty.c
*/
int								ft_tty_raw(struct termios base_term, int fd_in);
int								tty_reset(struct termios base_term, int fd_in);

/*
** display.c
*/
int								ft_pchar(int c);
void							fill_screen(t_save_select *sv, t_term_parameter *term);
void							display_name(t_save_select *sv, int i, int j, int current);
void							del_column(char **keys, int *i, int *j, t_term_parameter *term);
int								verif_place(t_term_parameter *term);
void							redisplay(t_term_parameter *term);

/*
** move_lst.c
*/
void							move_lst(t_term_parameter *term, int top);
void							move_head_lst(t_term_parameter *term, int nb);
void							move_end_lst(t_term_parameter *term, int nb);

/*
** move_termcat.c
*/
void							move_column(char **keys, int *i, int *j, size_t size_column);
void							move_line(char **keys, int *i, int *j, t_term_parameter *term, int top);

/*
** free.c
*/
void							free_term(t_term_parameter **term);
void							free_select(t_select **s);

/*
** signals.c
*/

void							signals_select(void);

#	endif
