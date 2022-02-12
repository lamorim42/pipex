/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:49:35 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/12 14:27:29 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

//Errors
# define ARGC_ERR "\e[0;31mWrong amount of arguments\n\e[0m"

//Boolean
# define TRUE 1
# define FALSE 0

//Pipe
# define READ 0
# define WRITE 1

typedef struct s_file
{
	const char	*name;
	int			fd;
	int			file_ok;
}				t_file;

typedef struct s_cmd
{
	char	*str;
	char	**args;
	char	*path;
}			t_cmd;

typedef struct s_data
{
	int		arg_c;
	char	**arg_v;
	char	**env_p;
	int		pid1;
	int		pid2;
	int		fd[2];
	int		exit_status;
	t_file	infile;
	t_file	outfile;
	t_cmd	cmd;
}			t_data;

void	ft_check_infile(t_file *infile);
void	ft_check_argc(t_data *data);
void	ft_check_fork(int pid);
void	ft_start_pipex(t_data *data);
void	ft_pipex(t_data *data);
void	ft_init_data(int arg_c, char **arg_v, char **env_p, t_data *data);
void	ft_gen_cmd_args(t_data *data);
void	ft_change_cmd(t_data *data);
void	ft_exec_cmd(t_data *data);
void	ft_clean_data(t_data *data);

// Legacy functions
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);

#endif
