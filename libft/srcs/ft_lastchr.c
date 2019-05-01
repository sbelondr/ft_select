/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:04:28 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:53:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_lastchr(const char *s, int c)
{
	int	cnt;
	int	last;

	last = -1;
	cnt = -1;
	while (s[++cnt])
		if (s[cnt] == c)
			last = cnt;
	if (last != -1)
		return (last);
	return (cnt);
}
