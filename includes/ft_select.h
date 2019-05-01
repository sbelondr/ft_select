/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 09:38:13 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/01 16:22:58 by sbelondr         ###   ########.fr       */
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

typedef struct	s_cmd
{
	char			*name;
	int				is_select;
	int				size;
	t_pos			*pos;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_sv_cmd
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*last;
}				t_sv_cmd;

/*
** list_cmd.c
*/

t_cmd			*init_cmd(void);
void			free_list_cmd(t_cmd **cmd);

/*
** list_save.c
*/

t_sv_cmd		*init_sv_cmd(void);
void			insert_sv_cmd(t_sv_cmd **sv, t_cmd *cmd);
void			next_sv_cmd(t_sv_cmd *sv);
void			first_sv_cmd(t_sv_cmd *sv);
size_t			size_sv_cmd(t_sv_cmd *sv);


#	endif
