/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:03:20 by lamorim           #+#    #+#             */
/*   Updated: 2022/02/12 14:04:12 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

void	ft_check_infile(t_file *infile)
{
	infile->fd = open(infile->name, O_RDONLY);
	if (infile->fd == -1)
	{
		infile->file_ok = FALSE;
		perror(infile->name);
	}
}
