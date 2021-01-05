/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:32:46 by sbelondr          #+#    #+#             */
/*   Updated: 2020/12/23 23:46:51 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*final;

	if (!s1)
		return (NULL);
	final = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!final)
		return (NULL);
	ft_strcpy(final, s1);
	return (final);
}
