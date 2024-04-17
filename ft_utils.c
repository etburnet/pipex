/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:42:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/17 17:46:36 by eburnet          ###   ########.fr       */
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

int	ft_copy_file(int fd1, int fd2)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	ssize_t	bytes_written;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd2, buffer, sizeof(buffer));
		bytes_written = write(fd1, buffer, bytes_read);
		if (bytes_written != bytes_read)
			return (1);
	}
	return (0);
}

int	ft_free_all(char ***cmd_tab, int *fd1, int *fd2, char *error)
{
	ft_free_split(*cmd_tab);
	close(*fd1);
	close(*fd2);
	perror(error);
	return (0);
}

void	ft_close(int *fd1, int *fd2)
{
	close(*fd1);
	close(*fd2);
}

int	ft_unlink_return(int argc, char *argv[])
{
	unlink(argv[argc - 1]);
	unlink("tempfd");
	return (0);
}
