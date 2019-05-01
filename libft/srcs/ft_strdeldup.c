/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdeldup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 08:50:33 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:57:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_strdeldup(char **str, char *src)
{
	if (!(str && src))
		return ;
	ft_strdel(&(*str));
	(*str) = ft_strdup(src);
}
