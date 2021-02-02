/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:14:44 by sbelondr          #+#    #+#             */
/*   Updated: 2021/02/01 09:15:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisascii(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isascii(str[i]))
			return (0);
	return (1);
}
