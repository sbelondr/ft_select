/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydelline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:37:24 by sbelondr          #+#    #+#             */
/*   Updated: 2021/12/11 16:32:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arraydelline(char ***src, int line)
{
	int		i;
	int		k;
	int		len;
	char	**dst;

	if ((!*src) || line < 0 || (!(*src)[line]))
		return ;
	len = ft_arraylen(*src);
	dst = (char **)malloc(sizeof(char *) * len);
	if (!dst)
		return ;
	i = -1;
	k = 0;
	while (++i < len)
		if (i != line)
			dst[k++] = ft_strdup((*src)[i]);
	dst[k] = NULL;
	ft_arraydel(&(*src));
	*src = ft_arraydup(dst);
	ft_arraydel(&dst);
}
