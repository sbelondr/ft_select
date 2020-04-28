/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:17:26 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/26 19:03:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_select		*init_select(char *str)
{
	t_select	*ptr;

	if (!(ptr = (t_select*)malloc(sizeof(t_select) * 1)))
		return (0);
	ptr->name = ft_strdup(str);
	ptr->is_select = 0;
	ptr->pos.x = 0;
	ptr->pos.y = 0;
	ptr->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

t_save_select	*init_save_select(t_select *s)
{
	t_save_select	*ptr;

	if (!(ptr = (t_save_select*)malloc(sizeof(t_save_select) * 1)))
		return (0);
	ptr->head = s;
	ptr->current = NULL;
	ptr->end = NULL;
	ptr->max_size = 0;
	ptr->size_lst = 0;
	return (ptr);
}

int				del_select(t_save_select *s)
{
	t_select	*prev;
	t_select	*next;

	if ((!s) || (!(s->current)))
		return (0);
	s->size_lst -= 1;
	prev = s->current->prev;
	next = s->current->next;
	if (!prev)
		s->head = next;
	if (!next)
		s->end = prev;
	ft_strdel(&(s->current->name));
	free(s->current);
	s->current = NULL;
	s->current = (next) ? next : prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	return (next ? 1 : 0);
}

void			aply_select_save(t_save_select *sv, t_select *c)
{
	size_t			len;

	sv->current = c;
	sv->size_lst += 1;
	len = ft_strlen(c->name);
	if (sv->max_size < len)
		sv->max_size = len;
}

t_save_select	*create_lst_select(char **src)
{
	t_select		*c;
	t_save_select	*sv;
	int				i;

	i = -1;
	c = NULL;
	sv = init_save_select(0);
	while (src[++i])
	{
		if (!c)
		{
			c = init_select(src[i]);
			sv->head = c;
		}
		else
		{
			c->next = init_select(src[i]);
			c->next->prev = c;
			c = c->next;
		}
		aply_select_save(sv, c);
	}
	sv->end = c;
	return (sv);
}
