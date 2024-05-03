/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:37:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/03 14:09:56 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_execute_command(char *cmd_path, char **cmd_tab, int fd1, int fd2)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_free_all(&cmd_tab, &fd1, &fd2, "fork"));
	else if (pid == 0)
	{
		dup2(fd1, STDIN_FILENO);
		close(fd1);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		execve(cmd_path, cmd_tab, NULL);
		free(cmd_path);
		return (ft_free_all(&cmd_tab, &fd1, &fd2, "execve"));
	}
	return (1);
}

int	ft_execute_command_with_path(char *cmd, int fd1, int fd2)
{
	char	*cmd_path;
	char	**cmd_tab;
	int		ret;

	cmd_tab = ft_split(cmd, ' ');
	if (cmd_tab == NULL)
	{
		ft_close(&fd1, &fd2);
		perror("ft_split");
		return (0);
	}
	cmd_path = ft_find_cmd(cmd_tab);
	if (cmd_path == NULL)
		return (ft_free_all(&cmd_tab, &fd1, &fd2, "ft_find_cmd"));
	ret = ft_execute_command(cmd_path, cmd_tab, fd1, fd2);
	ft_free_split(cmd_tab);
	free(cmd_path);
	return (ret);
}

int	ft_execute(char **argv, int argc, int fd1, int fd2)
{
	int		status;
	pid_t	pid;
	int		i;
	int		fd_pipe[2];

	i = 1;
	pid = 0;
	while (argv[i++] != NULL && i < argc - 2)
	{
		if (pipe(fd_pipe) == -1)
			return (perror("pipe"), 0);
		if (ft_execute_command_with_path(argv[i], fd1, fd_pipe[1]) == 0)
			return (ft_close(&fd_pipe[0], &fd_pipe[1]), 0);
		close(fd_pipe[1]);
		fd1 = fd_pipe[0];
	}
	if (ft_execute_command_with_path(argv[argc - 2], fd1, fd2) == 0)
		return (ft_close(&fd_pipe[0], &fd_pipe[1]), 0);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (!WIFEXITED(status))
			return (0);
	}
	return (ft_close(&fd1, &fd2), 1);
}
