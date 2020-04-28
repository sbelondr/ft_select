/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:16:20 by sbelondr          #+#    #+#             */
/*   Updated: 2020/04/28 09:23:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void	sig_action(int sig);

void		clean_screen(void)
{
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
}

void		act_sig_stop(t_term_parameter **term)
{
		int	def[2];

		def[0] = (*term)->base_term.c_cc[VSUSP];
		def[1] = 0;
		reset_term(*term);
		(*term)->base_term.c_lflag |= (ICANON | ECHO);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, def);
}

void	act_sig_cont(t_term_parameter **term)
{
		(*term)->base_term.c_lflag &= ~(ICANON | ECHO);
		(*term)->base_term.c_cc[VMIN] = 1;
		(*term)->base_term.c_cc[VTIME] = 0;
		tcsetattr(0, 0, &((*term)->base_term));
		signal(SIGTSTP, sig_action);
		tputs(tgetstr("vi", NULL), 1, ft_pchar);
		redisplay(*term);
		ft_select((*term)->select, *term);
		exit(0);
}

/*
** SIGWINCH --> resize window > clean display and re display
** SIGTSTP && SIGSTOP --> stop process > clean display and reset tty
** SIGCONT --> continue process if stopped > tty and re display all parameters
** other --> clear malloc, reset tty  and exit > use a sig for exit argument ?
*/
void	sig_action(int sig)
{
	t_term_parameter	**term;

	term = get_term_parameter(NULL);
	clean_screen();
	if (sig == SIGWINCH)
	{
		if (!verif_place(*term))
			ft_putstr_fd("Too many parameters compared to the size of the screen\n", STDERR_FILENO);
		else
			redisplay(*term);
	}
	else if (sig == SIGTSTP || sig == SIGSTOP)
		act_sig_stop(term);
	else if (sig == SIGCONT)
		act_sig_cont(term);
	else
	{
		reset_term(*term);
		free_term(term);
		ft_dprintf(STDERR_FILENO, "Quit: %d\n", sig);
		exit(sig);
	}
}

/*
** manage all signals (1 to 31)
*/
void	signals_select(void)
{
	int	sig;

	sig = 0;
	while (++sig < 32)
		signal(sig, sig_action);
}
