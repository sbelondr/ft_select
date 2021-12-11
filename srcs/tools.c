/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:13:08 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 16:13:04 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_pchar(int c)
{
	write(2, &c, 1);
	return (c);
}

int	verif_place(t_term_parameter *term)
{
	size_t	size_max;

	size_max = term->nb_column * term->line;
	return (size_max >= term->select->size_lst);
}

void	redisplay(t_term_parameter *term)
{
	calc_term(term);
	term->select->current = term->select->head;
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	fill_screen(term);
}

char	*get_final_value(t_select *s)
{
	char	*tmp;
	char	*src;
	int		first;

	first = 1;
	src = ft_strdup("");
	while (s)
	{
		if (s->is_select)
		{
			if (first)
				first = 0;
			else
			{
				tmp = ft_strjoin(src, " ");
				ft_strdel(&src);
				src = tmp;
			}
			tmp = ft_strjoin(src, s->name);
			ft_strdel(&src);
			src = tmp;
		}
		s = s->next;
	}
	return (src);
}

void	return_value(t_term_parameter *term)
{
	t_select	*s;
	char		*src;

	s = term->select->head;
	src = get_final_value(s);
	ft_putstr_fd(src, STDOUT_FILENO);
	ft_strdel(&src);
}
