/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:33:23 by sbelondr          #+#    #+#             */
/*   Updated: 2023/03/11 14:33:51 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	ft_reset_term(t_term_parameter **term)
{
	struct termios		base_term;

	base_term = (*term)->base_term;
	if (tcsetattr(0, TCSADRAIN, &base_term) == -1)
		exit(EXIT_FAILURE);
	tputs(tgoto(tgetstr("me", NULL), 0, 0), 1, ft_pchar);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(tgetstr("te", NULL), 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
}
