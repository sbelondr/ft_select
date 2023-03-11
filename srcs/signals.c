/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:16:20 by sbelondr          #+#    #+#             */
/*   Updated: 2023/03/11 14:33:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
** render terminal before render the default parameter
*/

static void	act_sig_stop(t_term_parameter **term)
{
	int				def[2];
	struct termios	base_term;

	(*term)->block_signal = 1;
	tputs(tgoto(tgetstr("me", NULL), 0, 0), 1, ft_pchar);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(tgetstr("te", NULL), 0);
	tputs(tgoto(tgetstr("ve", NULL), 0, 0), 1, ft_pchar);
	tcgetattr(0, &base_term);
	def[0] = base_term.c_cc[VSUSP];
	def[1] = 0;
	ft_reset_term(term);
	base_term.c_lflag |= (ICANON | ECHO);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, def);
	tputs(tgoto(tgetstr("me", NULL), 0, 0), 1, ft_pchar);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(tgetstr("te", NULL), 0);
	tputs(tgoto(tgetstr("ve", NULL), 0, 0), 1, ft_pchar);
	if (tcsetattr(0, TCSADRAIN, &base_term) == -1)
		exit(EXIT_FAILURE);
}

/*
** recalc column and line when terminal is resize, project start, ...
*/

void	select_resize(t_term_parameter **term)
{
	if ((*term)->block_signal)
		return ;
	tputs(tgoto(tgetstr("me", NULL), 0, 0), 1, ft_pchar);
	calc_term(*term);
	if (!verif_place(*term))
		manage_screen_small_start(*term);
	calc_term(*term);
	(*term)->coor.x = 0;
	(*term)->coor.y = 0;
	(*term)->select->current = (*term)->select->head;
	fill_screen(*term);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_pchar);
	display_name((*term)->select, 0, 0, 1);
}

/*
** fg
*/

static void	act_sig_cont(t_term_parameter **term)
{
	(*term)->base_term.c_lflag &= ~(ICANON | ECHO);
	(*term)->base_term.c_cc[VMIN] = 1;
	(*term)->base_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &((*term)->base_term));
	signal(SIGTSTP, sig_action);
	tputs(tgetstr("vi", NULL), 1, ft_pchar);
	(*term)->block_signal = 0;
	select_resize(term);
}

/*
** call function when is detect signal
**
** SIGWINCH --> resize window > clean display and re display
** SIGTSTP && SIGSTOP --> stop process > clean display and reset tty
** SIGCONT --> continue process if stopped > tty and re display all parameters
** other --> clear malloc, reset tty  and exit > use a sig for exit argument ?
*/

void	sig_action(int sig)
{
	t_term_parameter	**term;

	tputs(tgoto(tgetstr("me", NULL), 0, 0), 1, ft_pchar);
	term = get_term_parameter(NULL);
	tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_pchar);
	if (sig == SIGWINCH)
		select_resize(term);
	else if (sig == SIGTSTP)
		act_sig_stop(term);
	else if (sig == SIGCONT)
		act_sig_cont(term);
	else
	{
		reset_term(term, 1);
		dprintf(STDERR_FILENO, "Quit: %d\n", sig);
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
