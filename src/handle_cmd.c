/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:36:20 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/12 14:35:47 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_change_cmd(t_data *data)
{
	data->cmd.str = data->arg_v[3];
}

void	ft_gen_cmd_args(t_data *data)
{
	data->cmd.args = ft_split(data->cmd.str, ' ');
	if (!data->cmd.args)
	{
		write(STDOUT_FILENO, "Erro: command string generation!\n", 33);
		exit (3);
	}
}

void	ft_exec_cmd(t_data *data)
{
	if (!data->infile.file_ok)
	{
		write(STDOUT_FILENO, "\0", 1);
		return ;
	}
	if (execve(data->cmd.path, data->cmd.args, data->env_p) == -1)
	{
		perror("Erro execve");
		exit(127);
	}
}
