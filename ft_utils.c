/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:42:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/09 16:42:37 by eburnet          ###   ########.fr       */
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

int	ft_move_file(int fd1, int fd2)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	ssize_t	bytes_written;

	while ((bytes_read = read(fd2, buffer, sizeof(buffer))) > 0)
	{
		bytes_written = write(fd1, buffer, bytes_read);
		if (bytes_written != bytes_read)
			return (1);
	}
	return (0);
}