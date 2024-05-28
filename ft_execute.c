/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:37:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/27 14:51:06 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_forking(t_pipe_cmd pipe_cmd, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_free_all(&pipe_cmd.cmd_tab, "fork"));
	else if (pid == 0)
	{
		dup2(pipe_cmd.fd1, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		ft_close(pipe_cmd.fd1, fd);
		if (pipe_cmd.fd2 > 0)
		{
			close(pipe_cmd.fd_pipe[0]);
			close(pipe_cmd.fd2);
		}
		execve(pipe_cmd.cmd_path, pipe_cmd.cmd_tab, NULL);
		free(pipe_cmd.cmd_path);
		return (ft_free_all(&pipe_cmd.cmd_tab, "execve"));
	}
	ft_close(pipe_cmd.fd1, fd);
	return (1);
}

int	ft_path(char *cmd, t_pipe_cmd pipe_cmd, int i)
{
	int		ret;
	int		fd;

	if (i == 1)
		fd = pipe_cmd.fd_pipe[1];
	else
		fd = pipe_cmd.fd2;
	pipe_cmd.cmd_tab = ft_split(cmd, ' ');
	if (pipe_cmd.cmd_tab == NULL)
	{
		perror("ft_split");
		return (0);
	}
	pipe_cmd.cmd_path = ft_find_cmd(pipe_cmd.cmd_tab);
	if (pipe_cmd.cmd_path == NULL)
		return (ft_free_all(&pipe_cmd.cmd_tab, "ft_find_cmd"));
	ret = ft_forking(pipe_cmd, fd);
	ft_free_split(pipe_cmd.cmd_tab);
	free(pipe_cmd.cmd_path);
	return (ret);
}

int	ft_execute(char **argv, int argc, t_pipe_cmd pipe_cmd)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 1;
	pid = 0;
	while (argv[i++] != NULL && i < argc - 2)
	{
		if (pipe(pipe_cmd.fd_pipe) == -1)
			return (perror("pipe"), 0);
		if (ft_path(argv[i], pipe_cmd, 1) == 0)
			return (ft_close(pipe_cmd.fd_pipe[0], pipe_cmd.fd_pipe[1]), 0);
		close(pipe_cmd.fd_pipe[1]);
		pipe_cmd.fd1 = pipe_cmd.fd_pipe[0];
	}
	if (ft_path(argv[argc - 2], pipe_cmd, 0) == 0)
		return (ft_close(pipe_cmd.fd_pipe[0], pipe_cmd.fd_pipe[1]), 0);
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (!WIFEXITED(status))
			return (ft_close(pipe_cmd.fd_pipe[0], pipe_cmd.fd_pipe[1]), close(pipe_cmd.fd2), 0);
	}
	close(pipe_cmd.fd2);
	return (ft_close(pipe_cmd.fd1, pipe_cmd.fd2), ft_close(pipe_cmd.fd_pipe[0], pipe_cmd.fd_pipe[1]), 1);
}
