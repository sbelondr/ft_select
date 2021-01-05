/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:03:55 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:42:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fuck_norm(int negatif)
{
	if (negatif == 0)
		return (-1);
	return (0);
}

static int	ft_fuck_norm_bis(int negatif, int nb)
{
	if (nb == 0)
		return (0);
	if (negatif == 1)
		return (-nb);
	return (nb);
}

int	ft_atoi(const char *str)
{
	long	nb;
	int		cpt;
	int		negatif;

	nb = 0;
	negatif = 0;
	cpt = 0;
	while (ft_isspace(str[cpt]))
		cpt++;
	if (str[cpt] == '-' || str[cpt] == '+')
		if (str[cpt++] == '-')
			negatif = 1;
	while (str[cpt] && ft_isdigit(str[cpt]))
	{
		nb = (nb * 10) + str[cpt] - '0';
		if (nb < 0)
			return (ft_fuck_norm(negatif));
		cpt++;
	}
	return (ft_fuck_norm_bis(negatif, nb));
}
