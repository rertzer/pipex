/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:33:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 11:32:37 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	pp_check_cmd(t_ppdata *ppdata, char *cmd, char **envp)
{
	t_cmd	command;

	command = pp_init_cmd(ppdata, cmd);
	if (command.args[0] == NULL)
		return (command);
	if (ft_strchr(command.args[0], '/'))
		command.path = ft_strdup(command.args[0]);
	else
		command.path = pp_check_cmd_path(ppdata, command.args[0], envp);
	return (command);
}

char	*pp_check_cmd_path(t_ppdata *ppdata, char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	paths = pp_path_extract(ppdata, envp);
	i = -1;
	while (paths[++i])
	{
		cmd_path = pp_pathjoin(paths[i], cmd);
		if (cmd_path == NULL)
		{
			ft_split_flush(paths);
			pp_exit(ppdata, MAL_ER);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		pp_nullfree(&(cmd_path));
	}
	ft_split_flush(paths);
	if (NULL == cmd_path)
		ft_printf("pipex : command not found : %s\n", cmd);
	return (cmd_path);
}
