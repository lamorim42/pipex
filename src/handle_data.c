/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:42:09 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/15 20:45:27 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_data(int arg_c, char **arg_v, char **env_p, t_data *data)
{
	data->arg_c = arg_c;
	data->arg_v = arg_v;
	data->env_p = env_p;
	data->infile.name = data->arg_v[1];
	data->infile.file_ok = TRUE;
	data->cmd.str = data->arg_v[2];
	data->outfile.name = data->arg_v[4];
	data->cmd.args = NULL;
	data->cmd.path = NULL;
	data->exit_status = 0;
}

void	ft_clean_data(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		while (data->cmd.args[i])
		{
			free(data->cmd.args[i]);
			i++;
		}
		free(data->cmd.args);
		free(data->cmd.path);
	}
}

void	ft_free_mtx(char ***mtx)
{
	int	i;

	i = 0;
	while ((*mtx)[i])
	{
		free((*mtx)[i]);
		i++;
	}
	free(*mtx);
}
