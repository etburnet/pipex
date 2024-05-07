/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:08:42 by eburnet           #+#    #+#             */
/*   Updated: 2024/05/07 17:57:32 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_ex_here(char *cmd_path, char **cmd_tab, int *pipefd, char *limiter)
{
	pid_t	pid;
	char	buffer[1024];
	int		bytes_read;
	int		i;
	char	ch;
	int		len;

	len = ft_strlen(limiter);
	i = 0;
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		close(pipefd[0]);
		bytes_read = read(STDIN_FILENO, &ch, 1);
		while (bytes_read > 0)
		{
			buffer[i++] = ch;
			buffer[i] = '\0';
			if (buffer[i - 1] == '\n')
			{
				if (ft_strncmp(buffer + (ft_strlen(buffer) - len + 1), limiter, ft_strlen(buffer)))
				{
					if (buffer[ft_strlen(buffer) - (len + 1)] == '\n')
						break;
				}
			}
			bytes_read = read(STDIN_FILENO, &ch, 1);
		}
		close(pipefd[1]);
		execve(cmd_path, cmd_tab, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
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
	printf("%s\n", cmd_path);
	if (cmd_path == NULL)
		return (ft_free_split(cmd_tab), close(fd), 0);
	if (!ft_ex_here(cmd_path, cmd_tab, pipefd, argv[2]))
		return (free(cmd_path), ft_free_split(cmd_tab), close(fd), 0);
	if (ft_execute_command_with_path(argv[4], pipefd[0], fd) == 0)
		return (free(cmd_path), ft_free_split(cmd_tab), close(fd), 0);
	close(pipefd[0]);
	return (1);
}

