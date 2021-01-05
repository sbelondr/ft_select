/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:54:05 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:50:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	cnt;

	cnt = 0;
	if (!s)
		return (0);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (s[start] && len > 0)
	{
		str[cnt] = s[start++];
		--len;
		++cnt;
	}
	str[cnt] = 0;
	return (str);
}
