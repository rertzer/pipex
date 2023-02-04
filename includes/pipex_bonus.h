/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:59:04 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 11:24:18 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	char	*limiter;
	t_cmd	*commands;
	int		(*pipefd)[2];
	int		cmd_nb;
}	t_ppdata;

/* Init and Check func */
void	pp_init_ppdata(t_ppdata *ppdata, int argc, char **argv);
t_cmd	pp_init_cmd(t_ppdata *ppdata, char *cmd);
/* here doc */
void	pp_here_doc(t_ppdata *ppdata);
char	*pp_here_write_line(t_ppdata *ppdata, int limiter_size, char *line);
/* check_cmd */
char	*pp_check_cmd_path(t_ppdata *ppdata, char *cmd, char **envp);
char	*pp_check_path(t_ppdata *ppdata, char *cmd_path, char **envp);
char	**pp_path_extract(t_ppdata *ppdata, char **envp);
/* Run */
void	pp_run_pipe(t_ppdata *ppdata, char **envp);
void	pp_run_close_pipes(t_ppdata *ppdata);
void	pp_run_wait(t_ppdata *ppdata);
void	pp_run_make_pipes(t_ppdata *ppdata);
void	pp_run_fork(t_ppdata *ppdata, char **envp);
/* Father */
void	pp_run_dad(t_ppdata *ppdata, char **envp, pid_t child);
/* Son */
int		pp_open_in(t_ppdata *ppdata, int i);
int		pp_open_out(t_ppdata *ppdata, int i);
void	pp_run_child(t_ppdata *ppdata, char **envp, int i);
/* Exit func */
void	pp_exit(t_ppdata *ppdata, char *msg);
void	pp_exit_error(t_ppdata *ppdata, char *msg);
void	pp_flush(t_ppdata *ppdata);
/* Utils */
void	pp_nullfree(char **ptr);
int		pp_pipe_numbers(t_ppdata *ppdata);
char	*pp_pathjoin(char const *s1, char const *s2);
#endif
