/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:19:56 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:52:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_itoa(int n)
{
	long	nbr;
	int		size;
	int		negatif;
	char	*str;

	negatif = (n < 0) ? 1 : 0;
	nbr = (negatif) ? -(long)n : (long)n;
	size = ft_numlen(nbr) + negatif;
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	(negatif) ? str[0] = '-' : 0;
	str[ft_strlen(str)] = '\0';
	return (str);
}
