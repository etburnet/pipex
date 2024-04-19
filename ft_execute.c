/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:37:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/19 10:20:06 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_execute_command(char *cmd_path, char **cmd_tab, int fd1, int fd2)
{
	pid_t	pid;
	int		tmp_fd1;
	int		tmp_fd2;

	tmp_fd1 = dup(fd1);
	tmp_fd2 = dup(fd2);
	if (tmp_fd1 < 0 || tmp_fd2 < 0)
		return (ft_free_all(&cmd_tab, &fd1, &fd2, "dup"));
	pid = fork();
	if (pid == -1)
		return (ft_free_all(&cmd_tab, &fd1, &fd2, "fork"));
	else if (pid == 0)
	{
		if (dup2(tmp_fd1, STDIN_FILENO) < 0 || dup2(tmp_fd2, STDOUT_FILENO) < 0)
		{
			free(cmd_path);
			return (ft_free_all(&cmd_tab, &fd1, &fd2, "dup2"));
		}
		ft_close(&tmp_fd1, &tmp_fd2);
		execve(cmd_path, cmd_tab, NULL);
		free(cmd_path);
		return (ft_free_all(&cmd_tab, &fd1, &fd2, "execve"));
	}
	ft_close(&tmp_fd1, &tmp_fd2);
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

	i = 2;
	pid = 0;
	while (argv[i] != NULL && i < argc - 1)
	{
		if (ft_execute_command_with_path(argv[i], fd1, fd2) == 0)
			return (0);
		ft_close(&fd1, &fd2);
		fd2 = open(argv[argc - 1], O_RDWR);
		fd1 = open(argv[1], O_RDWR);
		i++;
	}
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (!WIFEXITED(status))
			return (0);
	}
	ft_close(&fd1, &fd2);
	return (1);
}
