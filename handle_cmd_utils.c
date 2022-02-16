/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:11:37 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/15 21:27:47 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_token(t_data *data, t_token *token)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->cmd.args[i][1] != '%')
		i++;
	temp = data->cmd.args[i];
	data->cmd.args[i] = token->start;
	free(temp);
}

void	ft_free_path(char ***arr, char **cmd)
{
	ft_free_mtx(arr);
	free(*cmd);
}
