/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:00:45 by lamorim           #+#    #+#             */
/*   Updated: 2022/01/29 19:50:16 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	s_len = 0;
	while (s[s_len])
		s_len++;
	dup = (char *) malloc(s_len + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < s_len + 1)
		dup[i] = s[i];
	return (dup);
}
