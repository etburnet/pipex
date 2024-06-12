/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/06/12 13:50:36 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	t_pipe_cmd	*pipe_cmd;

	if (argc == 5)
	{
		pipe_cmd = malloc(sizeof(t_pipe_cmd));
		if (!pipe_cmd)
			return (0);
		pipe_cmd->fd1 = -1;
		pipe_cmd->fd2 = -1;
		if (ft_execute(argv, argc, *pipe_cmd) == 1)
			return (ft_close(pipe_cmd->fd1, pipe_cmd->fd2), free(pipe_cmd), 1);
		return (ft_close(pipe_cmd->fd1, pipe_cmd->fd2), free(pipe_cmd), 0);
	}
	else
		ft_putstr_fd("4 and only 4 args accepted", 2);
	return (1);
}
