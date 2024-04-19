/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:08:42 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/19 13:31:26 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_ex_here(char *cmd_path, char **cmd_tab, int fd2, char *limiter)
{
	pid_t	pid;
	int		tmp_fd2;

	tmp_fd2 = dup(fd2);
	if (tmp_fd2 < 0)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		if (limiter != NULL)
		{
			
		}
		else
		{
			
		}
		execve(cmd_path, cmd_tab, NULL);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	close(tmp_fd2);
	return (1);
}

int	ft_here_doc(int argc, char *argv[])
{
	int		fd2;
	char	**cmd_tab1;
	char	**cmd_tab2;
	char	*cmd_path1;
	char	*cmd_path2;
	
	fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	cmd_tab1 = ft_split(argv[3], ' ');
	cmd_tab2 = ft_split(argv[4], ' ');
	cmd_path1 = ft_find_cmd(cmd_tab1);
	cmd_path2 = ft_find_cmd(cmd_tab2);
	if (cmd_path1 == NULL || cmd_path2 == NULL)
		return(0);
	ft_ex_here(cmd_path1, cmd_tab1, fd2, argv[2]);
	ft_ex_here(cmd_path2, cmd_tab2, fd2, NULL);
	return (1);
}
