/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:24:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/01 14:32:08 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pp_run_pipe(t_ppdata *ppdata, char **envp)
{
	pp_run_make_pipes(ppdata);
	pp_run_fork(ppdata, envp);
	pp_run_close_pipes(ppdata);
	pp_run_wait(ppdata);
	pp_exit(ppdata, NULL);
}

void	pp_run_close_pipes(t_ppdata *ppdata)
{
	int	i;

	i = -1;
	while (++i < pp_pipe_numbers(ppdata))
	{
		close(ppdata->pipefd[i][0]);
		close(ppdata->pipefd[i][1]);
	}
}

void	pp_run_wait(t_ppdata *ppdata)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < ppdata->cmd_nb)
		wait(&status);
}

void	pp_run_make_pipes(t_ppdata *ppdata)
{
	int	i;

	errno = 0;
	ppdata->pipefd = malloc(sizeof(int) * 2 * (pp_pipe_numbers(ppdata)));
	if (NULL == ppdata->pipefd)
		pp_exit_error(ppdata, "pp_run_make_pipes 1");
	i = -1;
	while (++i < pp_pipe_numbers(ppdata))
	{
		if (pipe(ppdata->pipefd[i]) == -1)
			pp_exit_error(ppdata, "pp_run_make_pipes 2");
	}
}

void	pp_run_fork(t_ppdata *ppdata, char **envp)
{
	int		i;
	pid_t	child;

	i = -1;
	while (++i < ppdata->cmd_nb)
	{
		child = fork();
		if (child == -1)
			pp_exit_error(ppdata, "pp_run_pipe 3");
		else if (child == 0)
			pp_run_child(ppdata, envp, i);
	}
}
