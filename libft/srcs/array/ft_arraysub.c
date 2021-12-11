/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraysub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:07:10 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 16:30:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arraysub(char **src, int start, int len)
{
	char	**dst;
	int		i;

	if (!src)
		return (NULL);
	i = -1;
	dst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dst)
		return (NULL);
	--start;
	while (++i < len && src[++start])
		dst[i] = ft_strdup(src[start]);
	dst[i] = NULL;
	return (dst);
}
