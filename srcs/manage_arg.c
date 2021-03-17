/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:01:06 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/17 09:52:55 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int				ft_check_blank(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' \
				|| str[i] == '\r' || str[i] == '\n')
			return (0);
	return (1);
}

/*
** check if argv give only empty string and not print characters
** Return: 1 or 0
*/

int				check_argv(char **av)
{
	int	i;
	int	is_not_valid;

	i = 0;
	is_not_valid = 0;
	while (av[++i])
		if (ft_strequ(av[i], "") || !ft_strisascii(av[i]) \
				|| !ft_check_blank(av[i]))
		{
			ft_dprintf(STDERR_FILENO, "You used an illegal character\n");
			is_not_valid = 1;
			break ;
		}
	return (is_not_valid);
}

/*
** add new element in t_select list
*/

t_select		*edit_lst_select(t_select *select, char **src, int i)
{
	select->next = init_select(src[i]);
	select->next->prev = select;
	select = select->next;
	return (select);
}

/*
** free t_save_select and t_select struct
*/

t_save_select	*clean_lst(t_save_select *sv, t_select *select)
{
	free(sv);
	free_select(&select);
	return (NULL);
}
