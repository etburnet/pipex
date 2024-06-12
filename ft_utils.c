/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:42:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/06/12 13:47:16 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free (tab[i++]);
	free (tab);
}

int	ft_free_all(char ***cmd_tab, char *error)
{
	ft_free_split(*cmd_tab);
	ft_putstr_fd(error, 2);
	return (1);
}

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 0)	
		close(fd1);
	if (fd2 > 0)
		close(fd2);
}
