/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:27:14 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/10 22:06:37 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.pipex.rt = pipe(data.pipex.fd);
	ft_check_pipe(&data);
	ft_init_data(argc, argv, envp, &data);
	ft_check_argc(&data);
	data.pid1 = fork();
	ft_check_fork(data.pid1);
	ft_start_pipex(&data);
	if (data.pid1 == 0 && data.cmd_ok)
	{
		ft_cmd_parsing(&data.cmd1);
		ft_gen_cmd_args(&data.cmd1);
		ft_exec_cmd(&data);
	}
	waitpid(data.pid1, NULL, 0);
	data.pid2 = fork();
	ft_check_fork(data.pid2);
	if (data.pid2 == 0)
	{
		ft_pipex(&data);
		ft_gen_cmd_args(&data.cmd2);
		ft_exec_cmd(&data);
	}
	waitpid(data.pid2, NULL, 0);
	return (0);
}

void	ft_init_data(int arg_c, char **arg_v, char **env_p, t_data *data)
{
	data->arg_c = arg_c;
	data->arg_v = arg_v;
	data->env_p = env_p;
	data->infile.name = data->arg_v[1];
	data->cmd1.str = data->arg_v[2];
	data->cmd2.str = data->arg_v[3];
	data->outfile.name = data->arg_v[4];
	data->cmd_ok = TRUE;
	data->cmd1.trim = FALSE;
	data->cmd1.split = FALSE;
	data->cmd1.args = NULL;
	data->cmd2.trim = FALSE;
	data->cmd2.split = FALSE;
	data->cmd2.args = NULL;
}

void	ft_check_argc(t_data *data)
{
	if (data->arg_c != 5)
	{
		write(STDOUT_FILENO, ARGC_ERR, 37);
		exit (1);
	}
}

void	ft_check_fork(int pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit (2);
	}
}

void	ft_check_pipe(t_data *data)
{
	if (data->pipex.rt == -1)
	{
		perror("pipe");
		exit (3);
	}
}

void	ft_start_pipex(t_data *data)
{
	if (data->pid1 == 0)
	{
		ft_check_infile(data);
		dup2(data->pipex.fd[1], STDOUT_FILENO);
		close(data->pipex.fd[0]);
		close(data->pipex.fd[1]);
	}
	else
	{
		waitpid(data->pid1, NULL, 0);
		close(data->pipex.fd[0]);
		close(data->pipex.fd[1]);
	}
}

void	ft_pipex(t_data *data)
{
	if (data->pid2 == 0)
	{
		data->outfile.fd = open(data->outfile.name, \
		O_WRONLY | O_CREAT, 0644);
		dup2(data->pipex.fd[0], STDIN_FILENO);
		dup2(data->outfile.fd, STDOUT_FILENO);
		close(data->pipex.fd[0]);
		close(data->pipex.fd[1]);
	}
	else
		waitpid(data->pid2, NULL, 0);
	close(data->pipex.fd[0]);
	close(data->pipex.fd[1]);
}

void	ft_check_infile(t_data *data)
{
	data->infile.fd = open(data->infile.name, O_RDONLY);
	if (data->infile.fd == -1)
	{
		data->cmd_ok = FALSE;
		perror(data->infile.name);
	}
}

void	ft_clean_data(t_data *data)
{
	ft_clean_cmd(&data->cmd1);
	ft_clean_cmd(&data->cmd2);
}

void	ft_clean_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->trim)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	//free(cmd->str);
	free(cmd->path);
}

void	ft_gen_cmd_args(t_cmd *cmd)
{
	if (cmd->str[0] == ' ')
	{
		cmd->str = ft_strtrim(cmd->str, " ");
		cmd->trim = TRUE;
	}
	if (ft_strchr(cmd->str, ' '))
	{
		cmd->split = TRUE;
		cmd->args = ft_split(cmd->str, ' ');
	}
	if (!cmd->args)
	{
		write(STDOUT_FILENO, "Erro: command string generation!\n", 33);
		exit (4);
	}
}

void	ft_exec_cmd(t_data *data)
{
	if (data->pid1 == 0)
	{
		ft_cmd_parsing(&data->cmd1);
		if (execve(data->cmd1.path, data->cmd1.args, data->env_p) == -1)
			perror("Erro execve 1");
	}
	if (data->pid2 == 0)
	{
		ft_cmd_parsing(&data->cmd2);
		if (execve(data->cmd2.path, data->cmd2.args, data->env_p) == -1)
			perror("Erro execve 2");
	}
}

void	ft_cmd_parsing(t_cmd *cmd)
{
	if (cmd->trim)
		cmd->path = ft_strjoin("/bin/", cmd->args[0]);
	else
		cmd->path = ft_strjoin("/bin/", cmd->str);
}