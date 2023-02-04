/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:46:23 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 11:23:25 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pp_open_in(t_ppdata *ppdata, int i)
{
	int	fd_in;

	errno = 0;
	if (i == 0)
	{
		if (ppdata->limiter == NULL)
		{
			fd_in = open(ppdata->filein_path, O_RDONLY);
			if (fd_in == -1)
				pp_exit_error(ppdata, ppdata->filein_path);
		}
		else
		{
			pp_here_doc(ppdata);
			fd_in = ppdata->pipefd[ppdata->cmd_nb - 1][0];
			close(ppdata->pipefd[ppdata->cmd_nb - 1][1]);
		}
	}
	else
		fd_in = ppdata->pipefd[i - 1][0];
	return (fd_in);
}

int	pp_open_out(t_ppdata *ppdata, int i)
{
	int	fd_out;
	int	flags;

	if (ppdata->limiter == NULL)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else
		flags = O_CREAT | O_APPEND | O_WRONLY;
	errno = 0;
	if (i == ppdata->cmd_nb - 1)
	{
		fd_out = open(ppdata->fileout_path, flags, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd_out == -1)
			pp_exit_error(ppdata, ppdata->fileout_path);
	}
	else
		fd_out = ppdata->pipefd[i][1];
	return (fd_out);
}

void	pp_run_child(t_ppdata *ppdata, char **envp, int i)
{
	int		fd_in;
	int		fd_out;
	char	*cmd_path;

	fd_in = pp_open_in(ppdata, i);
	fd_out = pp_open_out(ppdata, i);
	errno = 0;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		pp_exit_error(ppdata, "pp_run_child 2");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		pp_exit_error(ppdata, "pp_run_child 3");
	pp_run_close_pipes(ppdata);
	cmd_path = pp_check_cmd_path(ppdata, ppdata->commands[i].path, envp);
	if (NULL != cmd_path)
	{
		errno = 0;
		execve(cmd_path, ppdata->commands[i].args, envp);
		pp_nullfree(&cmd_path);
		pp_exit_error(ppdata, ppdata->commands[i].path);
	}
	close(fd_in);
	close(fd_out);
	pp_exit(ppdata, NULL);
}
