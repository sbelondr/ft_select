/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:40:57 by sbelondr          #+#    #+#             */
/*   Updated: 2020/05/03 13:46:47 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
** term_raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
** | INLCR | IGNCR | IXON);
** term_raw.c_oflag &= ~OPOST;
** term_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
** term_raw.c_cflag &= ~(CSIZE | PARENB);
** term_raw.c_cflag |= CS8;
** term_raw.c_cc[VMIN] = 1;
** term_raw.c_cc[VTIME] = 0;
** term_raw.c_oflag &= ~(OPOST);
** if (tcsetattr(fd_in, TCSANOW, &term_raw) < 0)
*/

int		ft_tty_raw(struct termios base_term, int fd_in)
{
	struct termios	term_raw;

	term_raw = base_term;
	term_raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	term_raw.c_cflag &= ~(CS8);
	term_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	term_raw.c_cc[VMIN] = 1;
	term_raw.c_cc[VTIME] = 0;
	if (tcsetattr(fd_in, TCSAFLUSH, &term_raw) < 0)
		return (-1);
	return (0);
}

/*
** if (tcsetattr(fd_in, TCSANOW, &base_term) < 0)
*/

int		tty_reset(struct termios base_term, int fd_in)
{
	if (tcsetattr(fd_in, TCSAFLUSH, &base_term) < 0)
		return (-1);
	base_term.c_lflag |= (ICANON | ECHO);
	return (0);
}
