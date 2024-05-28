/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:42:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/27 13:55:10 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	free (tab);
}

int	ft_free_all(char ***cmd_tab, char *error)
{
	ft_free_split(*cmd_tab);
	perror(error);
	return (0);
}

void	ft_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
