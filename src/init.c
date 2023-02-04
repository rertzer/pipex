/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:31:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 10:31:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pp_init_ppdata(t_ppdata *ppdata, char **argv, char **envp)
{
	ppdata->commands[0].path = NULL;
	ppdata->commands[1].path = NULL;
	ppdata->commands[0].args = NULL;
	ppdata->commands[1].args = NULL;
	ppdata->filein_path = argv[1];
	ppdata->fileout_path = argv[4];
	ppdata->commands[0] = pp_check_cmd(ppdata, argv[2], envp);
	ppdata->commands[1] = pp_check_cmd(ppdata, argv[3], envp);
}

t_cmd	pp_init_cmd(t_ppdata *ppdata, char *cmd)
{
	t_cmd	command;
	char	**args;

	args = ft_split(cmd, ' ');
	if (args == NULL)
		pp_exit(ppdata, SPLT);
	command.path = NULL;
	command.args = args;
	return (command);
}

char	**pp_path_extract(t_ppdata *ppdata, char **envp)
{
	char	*path;
	char	**paths;

	path = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			path = &((*envp)[5]);
			break ;
		}
		envp++;
	}
	if (path == NULL)
		pp_exit(ppdata, PTH_M);
	paths = ft_split(path, ':');
	if (paths == NULL)
		pp_exit(ppdata, SPLT);
	return (paths);
}
