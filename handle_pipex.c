/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:16:26 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/15 21:41:06 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_pipex(t_data *data)
{
	ft_check_argc(data);
	if (pipe(data->fd) == -1)
		exit(1);
}

void	ft_start_pipex(t_data *data)
{
	ft_find_path(data);
	dup2(data->infile.fd, STDIN_FILENO);
	dup2(data->fd[WRITE], STDOUT_FILENO);
	close(data->fd[WRITE]);
	close(data->fd[READ]);
	close(data->infile.fd);
}

void	ft_fork_one(t_data *data)
{
	if (data->pid1 == 0)
	{
		ft_check_infile(&data->infile);
		ft_gen_cmd_args(data);
		ft_start_pipex(data);
		ft_exec_cmd(data);
	}
}

void	ft_pipex(t_data *data)
{
	ft_find_path(data);
	dup2(data->fd[READ], STDIN_FILENO);
	dup2(data->outfile.fd, STDOUT_FILENO);
	close(data->fd[READ]);
	close(data->fd[WRITE]);
	close(data->outfile.fd);
}

void	ft_fork_two(t_data *data)
{
	if (data->pid2 == 0)
	{
		ft_change_cmd(data);
		ft_check_outfile(&data->outfile);
		ft_gen_cmd_args(data);
		ft_pipex(data);
		ft_exec_cmd(data);
	}
}
