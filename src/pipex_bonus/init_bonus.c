/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:41:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 11:33:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pp_init_ppdata(t_ppdata *ppdata, int argc, char **argv)
{
	int	i;
	int	offset;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		ppdata->limiter = argv[2];
		offset = 3;
	}
	else
	{
		ppdata->limiter = NULL;
		offset = 2;
	}
	ppdata->cmd_nb = argc - (offset + 1);
	errno = 0;
	ppdata->commands = malloc(sizeof(t_cmd) * ppdata->cmd_nb);
	if (NULL == ppdata->commands)
		pp_exit_error(ppdata, "pp_init_ppdata");
	i = -1;
	while (++i < ppdata->cmd_nb)
		ppdata->commands[i] = pp_init_cmd(ppdata, argv[i + offset]);
	ppdata->filein_path = argv[1];
	ppdata->fileout_path = argv[i + offset];
}

t_cmd	pp_init_cmd(t_ppdata *ppdata, char *cmd)
{
	t_cmd	command;
	char	**args;

	args = ft_split(cmd, ' ');
	if (args == NULL)
		pp_exit(ppdata, SPLT);
	command.path = ft_strdup(args[0]);
	command.args = args;
	return (command);
}
