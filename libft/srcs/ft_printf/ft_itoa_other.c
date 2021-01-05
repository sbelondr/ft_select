/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:19:56 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/24 00:56:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_unsigned(unsigned long long n)
{
	int		cnt;

	cnt = 0;
	while (n != 0)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

int	ft_len_long(long long n)
{
	int		cnt;

	cnt = 0;
	while (n != 0)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

char	*ft_itoa_long(long long n)
{
	unsigned long long	nbr;
	int					size;
	int					negatif;
	char				*str;

	negatif = 0;
	if (n < 0)
		negatif = 1;
	nbr = (long long)n;
	if (negatif)
		nbr *= -1;
	size = ft_len_long(nbr) + negatif;
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

char	*ft_itoa_s(short n)
{
	int		nbr;
	int		size;
	int		negatif;
	char	*str;

	negatif = 0;
	if (n < 0)
		negatif = 1;
	nbr = (int)n;
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
