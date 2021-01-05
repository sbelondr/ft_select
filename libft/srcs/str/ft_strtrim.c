/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:31:25 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:55:14 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s)
{
	int		cnt;
	int		i;
	int		last;
	char	*str;

	cnt = -1;
	last = -1;
	i = 0;
	if (!s)
		return (0);
	while (s[++cnt] && ft_white_space(s[cnt]) == 1)
		i++;
	while (s[++cnt])
		if (ft_white_space(s[cnt]) == 0)
			last = cnt;
	str = (char*)malloc(sizeof(char) * (cnt - (cnt - last - 1) - i + 1));
	if (!str)
		return (0);
	cnt = i;
	i = 0;
	while (s[cnt] && cnt <= last)
		str[i++] = s[cnt++];
	str[i] = 0;
	return (str);
}
