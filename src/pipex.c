/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:27:14 by lamorim           #+#    #+#             */
/*   Updated: 2022/01/29 19:48:59 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_init_data(argc, argv, &data);
	ft_check_argc(&data);
	data.pid = fork();
	ft_check_fork(&data);
	ft_check_infile(&data);
	return (0);
}

void	ft_init_data(int arg_c, char **arg_v, t_data *data)
{
	data->arg_c = arg_c;
	data->arg_v = arg_v;
	data->infile.name = data->arg_v[1];
	data->outfile.name = data->arg_v[4];
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
			write(STDOUT_FILENO, "\e[1;91m", 8);
			perror(data->infile.name);
			write(STDOUT_FILENO, "\e[0m", 8);
			exit(3);
		}
	}
	else
		waitpid(data->pid, NULL, 0);
}

void	ft_check_argc(t_data *data)
{
	if (data->arg_c != 5)
	{
		data->err = ft_strdup("\e[1;91mWrong amount of arguments\n\e[0m");
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
