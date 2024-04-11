/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/10 11:19:50 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;
	int	tempfd;
	int	i;

/* 	if (argc == 6 && argv[1] == "here_doc")
	{
		ft_here_doc();
	} */
	if (argc > 4)
	{
		fd1 = open(argv[1], O_RDWR);
		if (fd1 < 0)
		{
			perror("no such file or directory:");
			return (0);
		}	
		tempfd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644); //
		if (ft_execute(argv[2], fd1, tempfd) == 0) //
		{
			unlink("temp");
			return (0);
		}
		i = 3;
		while (i < argc - 2)
		{
			tempfd = open("temp", O_RDWR); //
			if (ft_execute(argv[i], tempfd, -2) == 0) //
			{
				unlink("temp");
				return (0);
			}
			fd1 = open("temp", O_RDWR | O_TRUNC);
			fd2 = open("tempX", O_RDWR);
			if (ft_move_file(fd1, fd2) == 1)
			{
				unlink("temp");
				unlink("tempX");
				return (0);
			}
			i++;
			unlink("tempX");
		}
		fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		tempfd = open("temp", O_RDWR); //
		if (ft_execute(argv[argc - 2], tempfd, fd2) == 0) //
		{
			unlink("temp");
			unlink(argv[argc - 1]);
			return (0);
		}
		close(fd1);
		close(fd2);
		close(tempfd);
		unlink("temp");
		return (1);
	}
	perror("There is less than 4 args");
	return (0);
}
