/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydisplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:08:33 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:51:08 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_arraydisplay(char **src)
{
	int	i;

	i = -1;
	if (!src)
		return ;
	while (src[++i])
		ft_putendl(src[i]);
}
