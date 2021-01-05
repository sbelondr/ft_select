/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_other_u_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:19:56 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 00:39:40 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_sc(signed char c)
{
	int		nbr;
	int		size;
	int		negatif;
	char	*str;

	negatif = 0;
	if (c < 0)
		negatif = 1;
	nbr = (int)c;
	if (negatif)
		nbr *= -1;
	size = ft_numlen(nbr) + negatif;
	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (negatif)
		str[0] = '-';
	str[ft_strlen(str)] = '\0';
	return (str);
}

char	*ft_itoa_ul(unsigned long long n)
{
	unsigned long long	nbr;
	int					size;
	char				*str;

	nbr = (unsigned long long)n;
	size = ft_len_unsigned(nbr);
	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		(str)[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

char	*ft_itoa_us(unsigned short n)
{
	int		nbr;
	int		size;
	char	*str;

	nbr = (int)n;
	size = ft_numlen(nbr);
	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}
