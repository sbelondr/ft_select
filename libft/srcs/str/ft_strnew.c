/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:05:45 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:49:16 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	cnt;

	cnt = -1;
	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (++cnt <= size)
		str[cnt] = 0;
	return (str);
}
