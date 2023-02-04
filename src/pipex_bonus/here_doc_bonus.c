/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:31:58 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/01 14:30:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pp_here_doc(t_ppdata *ppdata)
{
	int		limiter_size;
	char	*line;

	errno = 0;
	if (pipe(ppdata->pipefd[ppdata->cmd_nb - 1]) == -1)
		pp_exit_error(ppdata, "pp_here_doc");
	limiter_size = ft_strlen(ppdata->limiter);
	line = get_next_line(0);
	while (line)
		line = pp_here_write_line(ppdata, limiter_size, line);
}

char	*pp_here_write_line(t_ppdata *ppdata, int limiter_size, char *line)
{
	int	line_size;

	line_size = ft_strlen(line);
	if (!((line_size == limiter_size + 1) && \
			(ft_strncmp(line, ppdata->limiter, limiter_size) == 0)))
	{
		errno = 0;
		if (write(ppdata->pipefd[ppdata->cmd_nb - 1][1], line, line_size) \
				== -1)
		{
			free(line);
			pp_exit_error(ppdata, "pp_here_write_line");
		}
		free(line);
		line = get_next_line(0);
	}
	else
	{
		free(line);
		line = NULL;
	}
	return (line);
}
