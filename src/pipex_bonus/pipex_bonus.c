/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:15:19 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/04 11:18:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_ppdata	data;
	int			argmin;

	if (argc > 1 && (0 == ft_strncmp(argv[1], "here_doc", 9)))
		argmin = 6;
	else
		argmin = 5;
	if (argc < argmin)
	{
		ft_putendl_fd(ARG_NB, 2);
		return (1);
	}
	pp_init_ppdata(&data, argc, argv);
	pp_run_pipe(&data, envp);
	return (0);
}
