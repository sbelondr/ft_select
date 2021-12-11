/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:04:21 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 17:05:46 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void	send_tputs(char *str, int affcnt, int i, int j)
{
	char	*val_goto;
	char	*val_str;

	val_str = tgetstr(str, NULL);
	val_goto = tgoto(val_str, j, i);
	tputs(val_goto, affcnt, ft_pchar);
	val_goto = NULL;
	val_str = NULL;
}

void	manage_screen_small_start(t_term_parameter *term)
{
	send_tputs("cl", 1, 0, 0);
	send_tputs("cm", 1, 0, 0);
	if (!verif_place(term))
	{
		ft_putstr_fd("Too small\n",
			STDERR_FILENO);
		while (!verif_place(term))
			calc_term(term);
	}
}
