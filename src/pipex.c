/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:27:14 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/14 22:44:39 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init_data(argc, argv, envp, &data);
	ft_check_argc(&data);
	if (pipe(data.fd) == -1)
		exit(404);
	data.pid1 = fork();
	ft_check_fork(data.pid1);
	if (data.pid1 == 0)
	{
		ft_check_infile(&data.infile);
		ft_gen_cmd_args(&data);
		ft_start_pipex(&data);
		ft_exec_cmd(&data);
	}
	if (data.pid1 != 0)
	{
		data.pid2 = fork();
		ft_check_fork(data.pid1);
	}
	if (data.pid2 == 0)
	{
		ft_change_cmd(&data);
		ft_check_outfile(&data.outfile);
		ft_gen_cmd_args(&data);
		ft_pipex(&data);
		ft_exec_cmd(&data);
	}
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
