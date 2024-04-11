/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:37:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/10 09:50:38 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
extern char **environ;

char	**ft_search_path(void)
{
	char	*path;
	char	*trimmed;
	char	**splited;
	int		i;
	
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_strdup(environ[i]);
	trimmed = ft_strtrim(path, "PATH=");
	splited = ft_split(trimmed, ':');
	free(path);
	free(trimmed);
	return (splited);
}

char	*ft_find_cmd(char **cmd_tab)
{
	char	**path;
	char	*full_path;
	int		i;

	i = 0;
	if (cmd_tab[0] == NULL)
		return (NULL);
	
	path = ft_search_path();
	while (path[i] != NULL)
	{
		full_path = malloc(sizeof(char) * (ft_strlen(path[i]) + ft_strlen(cmd_tab[0]) + 2));
		if (full_path == NULL)
		{
			ft_free_split(path);
			return (NULL);
		}
		full_path[0] = '\0';
		ft_strlcat(full_path, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(full_path) + ft_strlen(cmd_tab[0]) + 1);
		if (access(full_path, X_OK) == 0)
			break ;
		i++;
		free(full_path);
		full_path = NULL;
	}
	ft_free_split(path);
	return (full_path);
}

int	ft_execute(char *cmd, int fd1, int fd2)
{
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_tab;
	int		tmp_fd1;
	int		tmp_fd2;

	cmd_tab = ft_split(cmd, ' ');
	if (fd2 == -2)
		fd2 = open("tempX", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((cmd_path = ft_find_cmd(cmd_tab)) == NULL)
	{
		ft_free_split(cmd_tab);
		close(fd1);
		close(fd2);
		perror("invalid command");
		return (0);
	}
	if ((tmp_fd1 = dup(fd1)) < 0 || (tmp_fd2 = dup(fd2)) < 0)
	{
		ft_free_split(cmd_tab);
		free(cmd_path);
		close(fd1);
		close(fd2); 
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		ft_free_split(cmd_tab);
		close(fd1);
		close(fd2);
		return (0);
	}
	else if (pid == 0)
	{
		if (dup2(tmp_fd1, STDIN_FILENO) < 0 || dup2(tmp_fd2, STDOUT_FILENO) < 0)
		{
			free(cmd_path);
			ft_free_split(cmd_tab);
			close(fd1);
			close(fd2);
			perror("dup");
			return (0);
		}
		close(tmp_fd1);
		close(tmp_fd2);
		execve(cmd_path, cmd_tab, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	free(cmd_path);
	ft_free_split(cmd_tab);
	close(fd1);
	close(fd2);
	return (1);
}
