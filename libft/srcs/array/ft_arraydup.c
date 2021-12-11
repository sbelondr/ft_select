/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:18:45 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 16:32:38 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arraydup(char **line)
{
	int		i;
	int		len;
	char	**dst;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
		++i;
	len = i;
	dst = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (line[++i] && i < len)
		dst[i] = ft_strdup(line[i]);
	dst[i] = NULL;
	return (dst);
}
