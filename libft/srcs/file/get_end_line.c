/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:48:31 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:05:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	get_end_line(char *file)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDWR);
	while (get_next_line(fd, &str) != -1)
		ft_strdel(&str);
	return (fd);
}
