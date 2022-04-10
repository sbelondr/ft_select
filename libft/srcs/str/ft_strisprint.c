/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:28:35 by sbelondr          #+#    #+#             */
/*   Updated: 2022/04/10 16:29:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisprint(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]))
			return (0);
	return (1);
}
