/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/09 08:09:46 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;
	int	tempfd;
	int	i;

	if (argc > 4)
	{
		fd1 = open(argv[1], O_RDWR);
		tempfd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (ft_execute(argv[2], fd1, tempfd) == 0)
			return (0);
		i = 3;
		while (i < argc - 2)
		{
			tempfd = open("temp", O_RDWR);
			if (ft_execute(argv[i], tempfd, -2) == 0)
				return (0);
			i++;
		}
		fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		tempfd = open("temp", O_RDWR);
		if (ft_execute(argv[argc - 2], tempfd, fd2) == 0)
			return (0);
		//unlink("temp");
		//unlink("tempx");
	}
	return (1);
}
