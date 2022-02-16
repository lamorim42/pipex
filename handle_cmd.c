/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:36:20 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/15 21:28:26 by lamorim          ###   ########.fr       */
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
	t_token	token;

	token.flag = FALSE;
	token.start = ft_strchr(data->cmd.str, SNG_QUOTE);
	if (token.start)
	{
		token.end = ft_strrchr(data->cmd.str, SNG_QUOTE);
		if (token.start != token.end && token.start[1] != token.end[0])
		{
			token.str = ft_substr(token.start, 1, \
			(token.end - token.start) - 1);
			ft_memset(token.start + 1, '%', (token.end - token.start) - 1);
			token.flag = TRUE;
		}
	}
	data->cmd.args = ft_split(data->cmd.str, ' ');
	if (!data->cmd.args)
	{
		write(STDOUT_FILENO, "Erro: command string generation!\n", 33);
		exit (3);
	}
	if (token.flag)
		ft_token(data, &token);
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
	path = ft_strchr(env_p[i], '=') + 1;
	return (path);
}

void	ft_find_path(t_data *data)
{
	char	**arr;
	char	*path;
	char	*cmd;
	int		i;

	i = -1;
	path = ft_search_path(data->env_p);
	arr = ft_split(path, COLON);
	cmd = ft_strjoin(SLASH, data->cmd.args[0]);
	while (arr[++i])
	{
		data->cmd.path = ft_strjoin(arr[i], cmd);
		if (data->cmd.path && !access(data->cmd.path, F_OK | X_OK))
		{
			ft_free_path(&arr, &cmd);
			return ;
		}
		else
		{
			free(data->cmd.path);
			data->cmd.path = NULL;
		}
	}
	ft_free_path(&arr, &cmd);
}

void	ft_exec_cmd(t_data *data)
{
	if (!data->infile.file_ok)
	{
		write(STDOUT_FILENO, "\0", 1);
		return ;
	}
	if (!data->cmd.path || \
	execve(data->cmd.path, data->cmd.args, data->env_p) == -1)
	{
		ft_putstr_fd(data->cmd.args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_clean_data(data);
		exit(127);
	}
}
