/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/03 14:12:29 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;

	if (argc == 6 && (strcmp(argv[1], "here_doc") == 0))
		return (ft_here_doc(argc, argv));
	if (argc > 4)
	{
		fd1 = open(argv[1], O_RDWR);
		if (fd1 < 0)
			return (perror("open"), 0);
		fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (ft_execute(argv, argc, fd1, fd2) == 0)
			return (ft_close(&fd1, &fd2), 0);
		ft_close(&fd1, &fd2);
		return (1);
	}
	perror("There is less than 4 args");
	return (0);
}
