/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:27:14 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/15 21:39:14 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init_data(argc, argv, envp, &data);
	ft_init_pipex(&data);
	data.pid1 = fork();
	ft_check_fork(data.pid1);
	ft_fork_one(&data);
	if (data.pid1 != 0)
	{
		data.pid2 = fork();
		ft_check_fork(data.pid1);
	}
	ft_fork_two(&data);
	if (data.pid1 != 0)
	{
		waitpid(data.pid1, &data.exit_status, WNOHANG);
		close(data.fd[WRITE]);
	}
	if (data.pid2 != 0)
	{
		waitpid(data.pid2, &data.exit_status, 0);
		close(data.fd[READ]);
	}
	return (WEXITSTATUS(data.exit_status));
}
