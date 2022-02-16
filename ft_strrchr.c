/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 13:46:31 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/13 20:36:02 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)s;
	if (c == 0)
		return (&str[len]);
	while (len)
	{
		if (str[len] == (char)c)
			return (&str[len]);
		len--;
	}
	if (str[len] == (char)c)
		return (&str[len]);
	return (0);
}
