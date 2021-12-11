/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:17:26 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 16:03:24 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
** init struct t_select
** Return: struct t_select
*/

t_select	*init_select(char *str)
{
	t_select	*ptr;

	ptr = (t_select *)malloc(sizeof(t_select) * 1);
	if (!ptr)
		return (0);
	ptr->name = ft_strdup(str);
	ptr->is_select = 0;
	ptr->pos.x = 0;
	ptr->pos.y = 0;
	ptr->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

/*
** init struct t_save_select
** Return: struct t_save_select
*/

t_save_select	*init_save_select(t_select *s)
{
	t_save_select	*ptr;

	ptr = (t_save_select *)malloc(sizeof(t_save_select) * 1);
	if (!ptr)
		return (0);
	ptr->head = s;
	ptr->current = NULL;
	ptr->end = NULL;
	ptr->max_size = 0;
	ptr->size_lst = 0;
	return (ptr);
}

/*
** delete the current element of  the linked list
** Return: 0 if it fails otherwise 1
*/

int	del_select(t_save_select *s)
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
	if (next)
		s->current = next;
	else
		s->current = prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	return (next != NULL);
}

/*
** move index current element and calc new size
*/

void	aply_select_save(t_save_select *sv, t_select *select)
{
	size_t			len;

	sv->current = select;
	sv->size_lst += 1;
	len = ft_strlen(select->name);
	if (sv->max_size < len)
		sv->max_size = len;
}

/*
** create new struct t_select and t_save_select to save argv data
** Return: struct t_save_data
*/

t_save_select	*create_lst_select(char **src)
{
	t_select		*select;
	t_save_select	*sv;
	int				i;

	i = -1;
	select = NULL;
	sv = init_save_select(0);
	while (src[++i])
	{
		if (!ft_strisascii(src[i]))
			return (clean_lst(sv, select));
		if (!ft_strequ(src[i], ""))
		{
			if (!select)
			{
				select = init_select(src[i]);
				sv->head = select;
			}
			else
				select = edit_lst_select(select, src, i);
			aply_select_save(sv, select);
		}
	}
	sv->end = select;
	return (sv);
}
