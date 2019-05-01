/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:27:17 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 15:54:03 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				cnt;
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		carac;

	cnt = -1;
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	carac = (unsigned char)c;
	while (++cnt < n)
	{
		d[cnt] = s[cnt];
		if (s[cnt] == carac)
			return ((d + cnt + 1));
	}
	return (NULL);
}
