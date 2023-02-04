/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:59:04 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 10:18:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

# include "libft.h"

/* ERROR MESSAGES */
# define ARG_NB "Error: Wrong number of arguments"
# define SPLT "Error: ft_split malloc error"
# define CMD_NF ": Error : command not found"
# define PTH_M "Error: PATH missing in env"
# define MAL_ER "Error: malloc error"

/* STRUCTURES */

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_ppdata
{
	char	*filein_path;
	char	*fileout_path;
	t_cmd	commands[2];
	int		pipefd[2];
}	t_ppdata;

/* Init and Check func */
void	pp_init_ppdata(t_ppdata *ppdata, char **argv, char **envp);
t_cmd	pp_init_cmd(t_ppdata *ppdata, char *cmd);
char	**pp_path_extract(t_ppdata *ppdata, char **envp);
/* check_cmd */
t_cmd	pp_check_cmd(t_ppdata *ppdata, char *cmd, char **envp);
char	*pp_check_cmd_path(t_ppdata *ppdata, char *cmd_path, char **envp);
/* Run */
void	pp_run_pipe(t_ppdata *ppdata, char **envp);
void	pp_print(t_ppdata *ppdata);
/* Son */
void	pp_run_child_one(t_ppdata *ppdata, char **envp);
void	pp_run_child_two(t_ppdata *ppdata, char **envp);
/* Exit func */
void	pp_exit(t_ppdata *ppdata, char *msg);
void	pp_exit_error(t_ppdata *ppdata, char *msg);
void	pp_flush(t_ppdata *ppdata);
/* Utils */
void	pp_nullfree(char **ptr);
char	*pp_pathjoin(char const *s1, char const *s2);
#endif
