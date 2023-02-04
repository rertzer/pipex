/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:23:15 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 10:36:41 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pp_run_child_one(t_ppdata *ppdata, char **envp)
{
	int	fd;

	close(ppdata->pipefd[0]);
	errno = 0;
	fd = open(ppdata->filein_path, O_RDONLY);
	if (fd == -1)
		pp_exit_error(ppdata, ppdata->filein_path);
	if (dup2(fd, STDIN_FILENO) == -1)
		pp_exit_error(ppdata, "pp_run_child 2");
	close(fd);
	if (dup2(ppdata->pipefd[1], STDOUT_FILENO) == -1)
		pp_exit_error(ppdata, "pp_run_child 3");
	if (NULL != ppdata->commands[0].path)
	{
		errno = 0;
		execve(ppdata->commands[0].path, ppdata->commands[0].args, envp);
		pp_exit_error(ppdata, ppdata->commands[0].path);
	}
	close(fd);
	close(ppdata->pipefd[1]);
	pp_exit(ppdata, NULL);
}

void	pp_run_child_two(t_ppdata *ppdata, char **envp)
{
	int	fd;

	close(ppdata->pipefd[1]);
	errno = 0;
	fd = open(ppdata->fileout_path, O_CREAT | O_TRUNC | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		pp_exit_error(ppdata, ppdata->fileout_path);
	if (dup2(fd, STDOUT_FILENO) == -1)
		pp_exit_error(ppdata, "pp_run_dad 2");
	if (dup2(ppdata->pipefd[0], STDIN_FILENO) == -1)
		pp_exit_error(ppdata, "pp_run_dad 3");
	if (NULL != ppdata->commands[1].path)
	{
		errno = 0;
		execve(ppdata->commands[1].path, ppdata->commands[1].args, envp);
		pp_exit_error(ppdata, ppdata->commands[1].path);
	}
	close(fd);
	close(ppdata->pipefd[0]);
	pp_exit(ppdata, NULL);
}
