/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:36:20 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/13 19:12:39 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_search_path(char **env_p);

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

static char	*ft_search_path(char **env_p)
{
	int		i;
	char	*path;

	i = 0;
	while (env_p[i++])
	{
		if (ft_strnstr(env_p[i], "PATH", 4))
			break ;
	}
	path = ft_strchr(env_p[i], '/');
	return (path);
}

void	ft_find_path(t_data *data)
{
	char	**arr;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	path = ft_search_path(data->env_p);
	arr = ft_split(path, COLON);
	cmd = ft_strjoin(SLASH, data->cmd.args[0]);
	while (TRUE)
	{
		data->cmd.path = ft_strjoin(arr[i], cmd);
		if (!access(data->cmd.path, F_OK))
		{
			ft_free_mtx(&arr);
			free(cmd);
			break ;
		}
		else
			free(data->cmd.path);
		i++;
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
