/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:16:32 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 16:53:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrjoin_end(char *str, char c)
{
	char	*dst;
	int		len;
	int		i;

	if (!str || !c)
		return (NULL);
	len = ft_strlen(str) + 1;
	dst = (char *)malloc(sizeof(char) * len + 1);
	i = -1;
	while (str[++i])
		dst[i] = str[i];
	dst[i++] = c;
	dst[i] = '\0';
	return (dst);
}
