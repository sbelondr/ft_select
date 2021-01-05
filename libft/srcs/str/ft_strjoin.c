/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:05:16 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:47:36 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		size;
	int		cnt;
	int		cnt_s;

	cnt = 0;
	cnt_s = -1;
	if (!s1 || !s2)
		return (0);
	size = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	while (s1[++cnt_s])
		str[cnt++] = s1[cnt_s];
	cnt_s = -1;
	while (s2[++cnt_s])
		str[cnt++] = s2[cnt_s];
	str[cnt] = 0;
	return (str);
}
