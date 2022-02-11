/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:27:14 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/11 11:29:54 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_cmd(t_data *data);

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
		ft_gen_cmd_args(&data);
		ft_pipex(&data);
		ft_exec_cmd(&data);
	}
	if (data.pid1 != 0)
		waitpid(data.pid1, NULL, 0);
	if (data.pid2 != 0)
		waitpid(data.pid2, NULL, 0);
	return (0);
}

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
	data->cmd.trim = FALSE;
	data->cmd.split = FALSE;
}

void	ft_change_cmd(t_data *data)
{
	data->cmd.str = data->arg_v[3];
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

void	ft_start_pipex(t_data *data)
{
	ft_check_infile(&data->infile);
	data->cmd.path = ft_strjoin("/bin/", data->cmd.args[0]);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	ft_check_infile(t_file *infile)
{
	infile->fd = open(infile->name, O_RDONLY);
	if (infile->fd == -1)
	{
		infile->file_ok = FALSE;
		perror(infile->name);
	}
}

void	ft_pipex(t_data *data)
{
	data->cmd.path = ft_strjoin("/bin/", data->cmd.args[0]);
	data->outfile.fd = open(data->outfile.name, \
	O_WRONLY | O_CREAT, 0644);
	dup2(data->fd[0], STDIN_FILENO);
	dup2(data->outfile.fd, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->outfile.fd);
}

void	ft_clean_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd.trim)
		free(data->cmd.str);
	while (data->cmd.args[i])
	{
		free(data->cmd.args[i]);
		i++;
	}
	free(data->cmd.args);
	free(data->cmd.path);
}

void	ft_gen_cmd_args(t_data *data)
{
	if (data->cmd.str[0] == ' ')
	{
		data->cmd.str = ft_strtrim(data->cmd.str, " ");
		data->cmd.trim = TRUE;
	}
	if (ft_strchr(data->cmd.str, ' '))
	{
		data->cmd.args = ft_split(data->cmd.str, ' ');
		if (!data->cmd.args)
		{
			write(STDOUT_FILENO, "Erro: command string generation!\n", 33);
			exit (3);
		}
		data->cmd.split = TRUE;
	}
	else
	{
		data->cmd.args = (char **)malloc(sizeof(char *) * 2);
		data->cmd.args[0] = ft_strdup(data->cmd.str);
		data->cmd.args[1] = NULL;
	}
}

void	ft_exec_cmd(t_data *data)
{
	if (execve(data->cmd.path, data->cmd.args, data->env_p) == -1)
		perror("Erro execve");
}
