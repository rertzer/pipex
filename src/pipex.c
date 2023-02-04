/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:15:19 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/04 11:07:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_ppdata	data;

	if (argc != 5)
	{
		ft_putendl_fd(ARG_NB, 2);
		return (1);
	}
	pp_init_ppdata(&data, argv, envp);
	pp_run_pipe(&data, envp);
	return (0);
}
