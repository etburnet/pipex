/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/19 10:26:48 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_opens(int *fd1, int *tempfd, char *argv[])
{
	*fd1 = open(argv[1], O_RDWR);
	if (*fd1 < 0)
	{
		perror("no such file or directory:");
		return (0);
	}
	*tempfd = open("tempfd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (ft_copy_file(*tempfd, *fd1) == 1)
	{
		unlink("tempfd");
		return (0);
	}
	close (*tempfd);
	return (1);
}

int	main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;
	int	tempfd;

	if (argc == 6 && (strcmp(argv[1], "here_doc") == 0))
		return (ft_here_doc(argc, argv));
	if (argc > 4)
	{
		if (ft_opens(&fd1, &tempfd, argv) == 0)
			return (0);
		fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (ft_execute(argv, argc, fd1, fd2) == 0)
			return (ft_unlink_return(argc, argv), close(tempfd));
		tempfd = open("tempfd", O_RDWR | O_CREAT | O_TRUNC, 0644);
		fd1 = open(argv[1], O_RDWR);
		if (ft_copy_file(fd1, tempfd) == 1)
			return (ft_unlink_return(argc, argv), close(tempfd));
		ft_close(&fd1, &fd2);
		close(tempfd);
		return (1);
	}
	perror("There is less than 4 args");
	return (0);
}
