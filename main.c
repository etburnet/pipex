/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/06/10 16:00:53 by eburnet          ###   ########.fr       */
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
		pipe_cmd->fd1 = open(argv[1], O_RDONLY);
		if (pipe_cmd->fd1 < 0)
		{
			perror(argv[1]);
			pipe_cmd->fd1 = open("/dev/null", O_RDONLY);
		}
		pipe_cmd->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipe_cmd->fd2 < 0)
			return (close(pipe_cmd->fd1), free(pipe_cmd),
				perror(argv[argc - 1]), 1);
		if (ft_execute(argv, argc, *pipe_cmd) == 1)
			return (ft_close(pipe_cmd->fd1, pipe_cmd->fd2), free(pipe_cmd), 1);
		return (ft_close(pipe_cmd->fd1, pipe_cmd->fd2), free(pipe_cmd), 0);
	}
	else
		ft_putstr_fd("4 and only 4 args accepted", 2);
	return (1);
}



// les commands quand l'une a une error les autres ne se lance pas OK
// infile et outfile en read only et write only OK
// si infile n'existe pas afficher un perror (ex : open) et ouvrir /dev/null OK
// ne as oublier de faire des test avec cat et sleep 