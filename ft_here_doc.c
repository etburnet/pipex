/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:08:42 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/03 15:01:11 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_ex_here(char *cmd_path, char **cmd_tab, int *pipefd, char *limiter)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDIN_FILENO);
		execve(cmd_path, cmd_tab, NULL);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ft_here_doc(int argc, char *argv[])
{
	int		fd;
	char	**cmd_tab;
	char	*cmd_path;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	cmd_tab = ft_split(argv[3], ' ');
	if (cmd_tab == NULL)
		return (close(fd), 0);
	cmd_path = ft_find_cmd(cmd_tab);
	if (cmd_path == NULL)
		return (ft_free_split(cmd_tab), close(fd), 0);
	ft_ex_here(cmd_path, cmd_tab, pipefd, argv[2]);
	if (ft_execute_command_with_path(argv[4], pipefd[0], fd) == 0)
		return (free(cmd_path), ft_free_split(cmd_tab), close(fd), 0);
	return (1);
}
