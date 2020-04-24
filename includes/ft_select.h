/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 09:38:13 by sbelondr          #+#    #+#             */
/*   Updated: 2020-04-24 23:21:27 by sbelondr         ###   ########.fr       */ 
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_SELECT_H
#	define FT_SELECT_H

#include "../libft/includes/libft.h"
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_select
{
	char	*name;
	int		is_select;
	t_pos	pos;
	struct s_select	*next;
	struct s_select	*prev;
}								t_select;

typedef struct	s_save_select
{
	t_select	*head;
	t_select	*current;
	t_select	*end;
	size_t		max_size;
	size_t		size_lst;
}								t_save_select;

typedef struct	s_term_parameter
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
}								t_term_parameter;

t_save_select	*create_lst_select(char **src);
void				del_select(t_save_select *s);

#	endif
