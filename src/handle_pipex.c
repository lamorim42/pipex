/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:16:26 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/14 23:11:46 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_start_pipex(t_data *data)
{
	ft_find_path(data);
	dup2(data->infile.fd, STDIN_FILENO);
	dup2(data->fd[WRITE], STDOUT_FILENO);
	close(data->fd[WRITE]);
	close(data->fd[READ]);
	close(data->infile.fd);
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
