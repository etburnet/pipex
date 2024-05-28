/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/27 15:43:08 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	t_pipe_cmd	*pipe_cmd;

	if (argc > 4)
	{
		pipe_cmd = malloc(sizeof(t_pipe_cmd));
		if (!pipe_cmd)
			return (0);
		pipe_cmd->fd1 = open(argv[1], O_RDWR);
		if (pipe_cmd->fd1 < 0)
			return (free(pipe_cmd), perror("open"), 0);
		pipe_cmd->fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (ft_execute(argv, argc, *pipe_cmd) == 0)
		{
			ft_close(pipe_cmd->fd1, pipe_cmd->fd2);
			free(pipe_cmd);
			return (0);
		}
		ft_close(pipe_cmd->fd1, pipe_cmd->fd2);
		free(pipe_cmd);
		return (1);
	}
	else
		perror("There is less than 4 args");
	return (0);
}
