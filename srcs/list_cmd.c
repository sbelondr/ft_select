/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:49:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/01 16:06:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static t_pos	*init_pos(void)
{
	t_pos	*pos;

	if (!(pos = (t_pos*)malloc(sizeof(t_pos) * 1)))
		return (NULL);
	pos->x = 0;
	pos->y = 0;
	return (pos);
}

static void		free_list_pos(t_pos **pos)
{
	free(*pos);
	(*pos) = NULL;
}

t_cmd			*init_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd) * 1)))
		return (NULL);
	cmd->name = NULL;
	cmd->is_select = 0;
	cmd->size = 0;
	cmd->pos = init_pos();
	cmd->next = NULL;
	return (cmd);
}

void			free_list_cmd(t_cmd **cmd)
{
	if ((!cmd) || (!(*cmd)))
		return ;
	if ((*cmd)->next)
		free_list_cmd(&((*cmd)->next));
	ft_strdel(&((*cmd)->name));
	free_list_pos(&((*cmd)->pos));
	free(*cmd);
	(*cmd) = NULL;
}
