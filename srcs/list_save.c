/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:00:03 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/01 16:18:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_sv_cmd	*init_sv_cmd(void)
{
	t_sv_cmd	*sv;

	if (!(sv = (t_sv_cmd*)malloc(sizeof(t_sv_cmd) * 1)))
		return (NULL);
	sv->head = init_cmd();
	sv->current = NULL;
	sv->last = NULL;
	return (sv);
}

void		insert_sv_cmd(t_sv_cmd **sv, t_cmd *cmd)
{
	if ((*sv)->current == NULL)
	{
		cmd->next = NULL;
		(*sv)->head->next = cmd;
		(*sv)->current = cmd;
	}
	else
	{
		(*sv)->current->next = cmd;
		(*sv)->current = (*sv)->current->next;
	}
}

void		next_sv_cmd(t_sv_cmd *sv)
{
	if (sv && sv->current)
		sv->current = sv->current->next;
}

void		first_sv_cmd(t_sv_cmd *sv)
{
	if (sv && sv->head->next)
		sv->current = sv->head->next;
}

size_t		size_sv_cmd(t_sv_cmd *sv)
{
	size_t	i;

	i = 0;
	if (sv)
	{
		first_sv_cmd(sv);
		while (sv->current != NULL)
		{
			i++;
			next_sv_cmd(sv);
		}
	}
	return (i);
}
