/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:40:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 11:28:41 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*pp_check_cmd_path(t_ppdata *ppdata, char *cmd, char **envp)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
		path = ft_strdup(cmd);
	else
		path = pp_check_path(ppdata, cmd, envp);
	return (path);
}

char	*pp_check_path(t_ppdata *ppdata, char *cmd, char **envp)
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
	{
		ft_putstr_fd("pipex : command not found : ", 2);
		ft_putendl_fd(cmd, 2);
	}
	return (cmd_path);
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
