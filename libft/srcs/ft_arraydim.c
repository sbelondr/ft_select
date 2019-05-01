/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:55:54 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/25 18:56:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	***ft_arrays_dim(int n, ...)
{
	int		i;
	va_list	ap;
	char	**data;
	char	***final;

	va_start(ap, n);
	if (!(final = (char***)malloc(sizeof(char**) * (n + 1))))
		return (NULL);
	i = -1;
	while (++i < n)
	{
		data = va_arg(ap, char**);
		final[i] = ft_arraydup(data);
	}
	final[i] = NULL;
	va_end(ap);
	return (final);
}

void	ft_arrays_dim_del(char ****lst)
{
	int	i;

	i = -1;
	if ((!lst) || (!(*lst)))
		return ;
	while ((*lst)[++i])
		ft_arraydel(&((*lst)[i]));
	free(*lst);
	(*lst) = NULL;
}
