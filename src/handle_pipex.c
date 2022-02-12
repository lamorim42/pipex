/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:16:26 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/12 14:29:24 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_start_pipex(t_data *data)
{
	ft_check_infile(&data->infile);
	data->cmd.path = ft_strjoin("/bin/", data->cmd.args[0]);
	dup2(data->infile.fd, STDIN_FILENO);
	dup2(data->fd[WRITE], STDOUT_FILENO);
	close(data->fd[WRITE]);
	close(data->fd[READ]);
	close(data->infile.fd);
}

void	ft_pipex(t_data *data)
{
	data->cmd.path = ft_strjoin("/bin/", data->cmd.args[0]);
	data->outfile.fd = open(data->outfile.name, \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(data->fd[READ], STDIN_FILENO);
	dup2(data->outfile.fd, STDOUT_FILENO);
	close(data->fd[READ]);
	close(data->fd[WRITE]);
	close(data->outfile.fd);
}
