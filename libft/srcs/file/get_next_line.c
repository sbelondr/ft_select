/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:18:29 by apruvost          #+#    #+#             */
/*   Updated: 2020/12/23 23:16:43 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_new_line(char **s, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		++len;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = ft_strdup(s[fd] + len + 1);
		ft_strdel(&(s[fd]));
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUF_S)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&(s[fd]));
	}
	return (1);
}

static int	ft_fuck_norm(char **s, char **line, int fd, int ret)
{
	if (ret < 0 || (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0')))
		return (ret);
	return (ft_new_line(s, line, fd, ret));
}

int	get_next_line(const int fd, char **line)
{
	static char	*s[255];
	char		buf[BUF_S + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || line == NULL || fd >= 255)
		return (-1);
	ret = 0;
	while (ret > 0)
	{
		ret = read(fd, buf, BUF_S);
		if (ret > 0)
		{
			buf[ret] = '\0';
			if (s[fd] == NULL)
				s[fd] = ft_strnew(1);
			tmp = ft_strjoin(s[fd], buf);
			ft_strdel(&(s[fd]));
			s[fd] = tmp;
			if (ft_strchr(buf, '\n'))
				break ;
		}
	}
	return (ft_fuck_norm(s, line, fd, ret));
}
