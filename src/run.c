/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:20:54 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/01 10:42:03 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pp_run_pipe(t_ppdata *ppdata, char **envp)
{
	pid_t	child_one;
	pid_t	child_two;

	errno = 0;
	if (pipe(ppdata->pipefd) == -1)
		pp_exit_error(ppdata, "pp_run_pipe 1");
	child_one = fork();
	if (child_one == -1)
		pp_exit_error(ppdata, "pp_run_pipe 2");
	else if (child_one == 0)
		pp_run_child_one(ppdata, envp);
	else
	{
		child_two = fork();
		if (child_two == -1)
			pp_exit_error(ppdata, "pp_run_pipe 3");
		else if (child_two == 0)
			pp_run_child_two(ppdata, envp);
	}
	close(ppdata->pipefd[0]);
	close(ppdata->pipefd[1]);
	wait(NULL);
	wait(NULL);
	pp_exit(ppdata, NULL);
}
