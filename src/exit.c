/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:58:06 by rertzer           #+#    #+#             */
/*   Updated: 2023/01/30 13:43:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pp_exit(t_ppdata *ppdata, char *msg)
{
	if (NULL != msg)
		ft_putendl_fd(msg, 2);
	pp_flush(ppdata);
	exit(1);
}

void	pp_exit_error(t_ppdata *ppdata, char *msg)
{
	perror(msg);
	pp_flush(ppdata);
	exit(1);
}

void	pp_flush(t_ppdata *ppdata)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (ppdata->commands[i].path)
			pp_nullfree(&(ppdata->commands[i].path));
		if (ppdata->commands[i].args)
			ppdata->commands[i].args = ft_split_flush(ppdata->commands[i].args);
	}
}
