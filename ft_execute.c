/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:37:54 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/05 14:30:11 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
extern char **environ;

int	ft_move_file(int fd1, int fd2)
{
	int		bytes_read;
	int		bytes_wrote;
	int		buffer_size;
	char	*buff;

	buffer_size = 4096;
	buff = NULL;
	while ((bytes_read = read(fd2, buff, buffer_size)) > 0)
	{
		bytes_wrote = write(fd1, buff, bytes_read);
		if (bytes_wrote == -1)
		{
			close (fd1);
			close (fd2);
			return (1);
		}
	}
	return (0);	
}

char	*ft_search_path(void)
{
	char	*path;
	int		i;
	
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_strdup(environ[i]);
	return (path);
}

char	*ft_cmd_exist(char **cmd_tab)
{
	char	**path;
	char	*full_path;
	int		i;
	int		len_cmd;
	char	*splited;

	i = 0;
	if (cmd_tab[0] == NULL)
		return (NULL);
	len_cmd = ft_strlen(cmd_tab[0]);
	splited = ft_search_path();
	splited = ft_strtrim(splited, "PATH=");
	path = ft_split(splited, ':');
	while (path[i] != NULL)
	{
		full_path = malloc(sizeof(char) * (ft_strlen(path[i]) + len_cmd + 2));
		if (full_path == NULL)
			return (NULL);
		ft_strlcat(full_path, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(full_path) + len_cmd + 1);
		if (access(full_path, X_OK) == 0)
			break ;
		i++;
	}
	return (full_path);
}

int ft_execute(char *cmd, int fd1, int fd2)
{
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_tab;

	cmd_tab = ft_split(cmd, ' ');
	if (fd2 == -2)
		fd2 = open("tempEx", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((cmd_path = ft_cmd_exist(cmd_tab)) == NULL)
		return (0); //
	pid = fork();
	if (pid == -1)
		return (0); //
	else if (pid == 0)
	{
		ft_printf("%s, %s\n", cmd_path, cmd_tab[1]);
		dup2(fd1, STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		execve(cmd_path, cmd_tab, NULL);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (ft_move_file(fd1, fd2) == 1)
		{
			unlink("tempEx");
			return (0);
		}
	}
	unlink("tempEx");
	return (1);
}
