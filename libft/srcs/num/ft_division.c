/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_division.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:36:52 by samuel            #+#    #+#             */
/*   Updated: 2020/04/30 12:36:55 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_division(int a, int b)
{
	if (a == 0 || b == 0)
		return (0);
	return (a / b);
}