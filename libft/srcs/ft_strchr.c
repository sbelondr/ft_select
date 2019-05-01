/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 00:13:20 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:56:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		cnt;

	cnt = -1;
	while (s[++cnt])
		if (s[cnt] == c)
			return ((char*)s + cnt);
	if (c == '\0')
		return ((char*)s + cnt);
	return (0);
}
