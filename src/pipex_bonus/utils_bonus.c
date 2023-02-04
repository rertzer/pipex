/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:42:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/03 11:23:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pp_nullfree(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int	pp_pipe_numbers(t_ppdata *ppdata)
{
	int	nb;

	nb = ppdata->cmd_nb;
	if (ppdata->limiter == NULL)
		nb--;
	return (nb);
}

char	*pp_pathjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = ft_strlen(s1);
	i += ft_strlen(s2);
	dest = malloc(sizeof(char) *(i + 2));
	if (NULL == dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '/';
	i++;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
