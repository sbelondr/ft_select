/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:47:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/01 16:32:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*
 ** http://manpagesfr.free.fr/man/man3/termios.3.html
 ** http://www.cs.uleth.ca/~holzmann/C/system/ttyraw.c
 ** termios.truc |= (); -> active flag
 ** termios.truc &= ~(); -> desactive flag
 */

int		ft_tty_raw(struct termios base_term, int fd_in)
{
	struct termios	term_raw;


	term_raw = base_term;
//	term_raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
//			| INLCR | IGNCR | IXON);
//	term_raw.c_oflag &= ~OPOST;
//	term_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
//	term_raw.c_cflag &= ~(CSIZE | PARENB);
//	term_raw.c_cflag |= CS8;
//	term_raw.c_cc[VMIN] = 1;
//	term_raw.c_cc[VTIME] = 0;


	   term_raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	//term_raw.c_oflag &= ~(OPOST);
	term_raw.c_cflag &= ~(CS8);
	term_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);// | ISIG);
	term_raw.c_cc[VMIN] = 1;
	term_raw.c_cc[VTIME] = 0;
	//if (tcsetattr(fd_in, TCSANOW, &term_raw) < 0)
	if (tcsetattr(fd_in, TCSAFLUSH, &term_raw) < 0)
		return (-1);
	return (0);
}

int		tty_reset(struct termios base_term, int fd_in)
{
	//if (tcsetattr(fd_in, TCSANOW, &base_term) < 0)
	if (tcsetattr(fd_in, TCSAFLUSH, &base_term) < 0)
		return (-1);
	return (0);
}

int	ft_pchar(int c)
{
	write(1, &c, 1);
	return (c);
}

char	*test(char **list_arg)
{
	int		i;
	int		j;
	char	*keys[10];
	char	*final;
	char	*term;
	char	buf[3];

	term = getenv("TERM");
	if ((!term) || tgetent(0, term) == -1)
	{
		ft_dprintf(2, "Error: tgetent doesn't work!\n");
		return (NULL);
	}
	keys[0] = tgetstr("cm", NULL);
	keys[1] = tgetstr("cl", NULL);
	keys[2] = tgetstr("kd", NULL);
	keys[3] = tgetstr("ku", NULL);
	keys[4] = tgetstr("kl", NULL);
	keys[5] = tgetstr("kr", NULL);
	keys[6] = tgetstr("DC", NULL);
	keys[7] = tgetstr("ts", NULL);

	tputs(keys[1], 1, ft_pchar);
	i = -1;
	while (list_arg[++i])
	{
		tputs(list_arg[i], 1, ft_pchar);//ft_printf("%s\t", list_arg[i]);
		tputs("\t", 1, ft_pchar);//ft_printf("%s\t", list_arg[i]);
	}
	i = 0;
	j = 0;
	tputs(tgoto(keys[0], 0, i), 1, ft_pchar);
	ft_bzero(buf, 3);
	while (read(0, buf, 3))
	{
		if ((buf[0] == 27 || buf[0] == 10) && buf[1] == 0)
			break ;
		else if (buf[0] == 32 && buf[1] == 0)
		{
			tputs(tgoto(tgetstr("so", NULL), j, i), 1, ft_pchar);
			tputs(tgoto(tgetstr("sa", NULL), j, i), 1, ft_pchar);
			tputs(list_arg[0], 1, ft_pchar);
			tputs(tgoto(tgetstr("se", NULL), j, i), 1, ft_pchar);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51)
			tputs(tgoto(keys[6], j, i), 1, ft_pchar);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
			tputs(tgoto(keys[0], j, --i), 1, ft_pchar);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
			tputs(tgoto(keys[0], j, ++i), 1, ft_pchar);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
			tputs(tgoto(keys[0], ++j, i), 1, ft_pchar);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		{
			//tputs(tgoto(tgetstr("us", NULL), j, i), 1, ft_pchar);
			//tputs(list_arg[0], 1, ft_pchar);
			tputs(tgoto(keys[0], --j, i), 1, ft_pchar);
			//tputs(tgoto(tgetstr("ue", NULL), j, i), 1, ft_pchar);
		}
		ft_bzero(buf, 3);
	}
	final = NULL;
	return (final);	
}

t_sv_cmd	*create_list(char **av)
{
	int			i;
	t_sv_cmd	*sv;
	t_cmd		*cmd;

	i = -1;
	sv = init_sv_cmd();
	while (av[++i])
	{
		cmd = init_cmd();
		cmd->name = ft_strdup(av[i]);
		cmd->size = ft_strlen(cmd->name);
		insert_sv_cmd(&sv, cmd);
		free_list_cmd(&cmd);
	}
	first_sv_cmd(sv);
	return (sv);
}

int		main(int ac, char **av)
{
	char					*final;
	static	int				fd_in;
	static	struct termios	base_term;

	
	t_sv_cmd	*sv = create_list(av + 1);
	while (sv->current)
	{
		ft_printf("%s\n", sv->current->name);
		next_sv_cmd(sv);
	}
	return (0);


	fd_in = STDIN_FILENO;
	if (tcgetattr(fd_in, &base_term) < 0)
		return (-1);
	if (ft_tty_raw(base_term, fd_in) == -1)
	{
		ft_dprintf(2, "Error: raw doesn't work!\n");
		return (-1);
	}
	if (ac > 1)
	{
//		t_sv_cmd	*sv = create_list(av + 1);
		final = test(av + 1);
	}
	if (tty_reset(base_term, fd_in) == -1)
	{
		ft_dprintf(2, "Error: reset raw doesn't work!\n");
		return (-1);
	}
	return (0);
}
