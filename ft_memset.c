/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:46:36 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/14 11:43:28 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*s;

	s = (char *) str;
	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}
