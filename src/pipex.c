/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:27:14 by lamorim           #+#    #+#             */
/*   Updated: 2022/01/30 05:51:02 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_cmd(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init_data(argc, argv, envp, &data);
	ft_check_argc(&data);
	data.pid = fork();
	ft_check_fork(&data);
	ft_check_infile(&data);
	if (data.pid == 0)
	{
		ft_gen_cmd_args(&data);
		printf("%s\n%s\n", data.cmd.args[0], data.cmd.args[1]);
		ft_exec_cmd(&data);
		ft_clean_data(&data);
	}
	else
		waitpid(data.pid, NULL, 0);
	return (0);
}

void	ft_init_data(int arg_c, char **arg_v, char **env_p, t_data *data)
{
	data->arg_c = arg_c;
	data->arg_v = arg_v;
	data->env_p = env_p;
	data->infile.name = data->arg_v[1];
	data->cmd.str = data->arg_v[2];
	data->outfile.name = data->arg_v[4];
	data->cmd.trim = FALSE;
}

void	ft_check_argc(t_data *data)
{
	if (data->arg_c != 5)
	{
		data->err = ft_strdup(ARGC_ERR);
		write(STDOUT_FILENO, data->err, 37);
		free(data->err);
		exit (1);
	}
}

void	ft_check_fork(t_data *data)
{
	if (data->pid == -1)
	{
		perror("fork");
		exit (2);
	}
}

void	ft_check_infile(t_data *data)
{
	if (data->pid == 0)
	{
		data->infile.fd = open(data->infile.name, O_RDONLY);
		if (data->infile.fd == -1)
		{
			data->outfile.fd = open(data->outfile.name, \
			O_WRONLY | O_CREAT, 0644);
			close(data->outfile.fd);
			write(STDOUT_FILENO, "\e[0;31m", 8);
			perror(data->infile.name);
			write(STDOUT_FILENO, "\e[0m", 8);
		}
		//olhar função ft_pipex em olayground
	}
	else
		waitpid(data->pid, NULL, 0);
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
		data->cmd.args = ft_split(data->cmd.str, ' ');
	if (!data->cmd.args)
	{
		write(STDOUT_FILENO, "Erro: command string generation!\n", 33);
		exit (3);
	}
}

void	ft_exec_cmd(t_data *data)
{
	data->cmd.path = ft_strjoin("/bin/", data->cmd.args[0]);
	printf("%s\n", data->cmd.path);
	if (data->pid == 0)
		data->f = execve(data->cmd.path, data->cmd.args, data->env_p);
	if (data->f == -1)
		printf("Erro execve\n");
}
