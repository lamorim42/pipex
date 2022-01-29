/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:49:35 by lamorim           #+#    #+#             */
/*   Updated: 2022/01/29 19:49:36 by lamorim          ###   ########.fr       */
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

typedef struct s_file
{
	const char	*name;
	int			fd;
}				t_file;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

typedef struct s_data
{
	int		arg_c;
	char	**arg_v;
	int		pid;
	t_file	infile;
	t_file	outfile;
	t_cmd	cmd_one;
	t_cmd	cmd_two;
	char	*err;
}			t_data;

void	ft_check_infile(t_data *data);
void	ft_check_argc(t_data *data);
void	ft_check_fork(t_data *data);
void	ft_init_data(int arg_c, char **arg_v, t_data *data);

// Legacy functions
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);

#endif
