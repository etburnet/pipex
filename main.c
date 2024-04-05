/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/05 14:26:32 by eburnet          ###   ########.fr       */
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
		fd2 = open(argv[argc-1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		tempfd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (ft_execute(argv[2], fd1, tempfd) == 0)
			return (ft_printf("exe 1 fail\n"));
		i = 3;
		while (i < argc - 2)
		{
			if (ft_execute(argv[i++], fd1, -2) == 0)
				return (ft_printf("exe fail\n"));
		}
		if (ft_execute(argv[argc - 2], tempfd, fd2) == 0)
			return (ft_printf("exe fail\n"));
		//unlink("temp");
	}
	return (1);
}
