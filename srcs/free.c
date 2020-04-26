/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 18:25:21 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/26 19:08:58 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	free_select(t_select **s)
{
	t_select *next;

	while (*s)
	{
		next = (*s)->next;
		ft_strdel(&((*s)->name));
		free(*s);
		(*s) = NULL;
		(*s) = next;
	}
}

void	free_term(t_term_parameter **term)
{
	free_select(&((*term)->select->head));
	free((*term)->select);
	(*term)->select = NULL;
	free(*term);
	*term = NULL;
}
