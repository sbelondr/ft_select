/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:19:56 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:38:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fuck_norm(int size, int negatif)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	if (negatif)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		size;
	int		negatif;
	char	*str;

	negatif = 0;
	nbr = (long)n;
	if (n < 0)
	{
		negatif = 1;
		nbr *= -1;
	}
	size = ft_numlen(nbr) + negatif;
	str = ft_fuck_norm(size, negatif);
	if (!str)
		return (0);
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
