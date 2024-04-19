/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:06:45 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/18 09:38:20 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_extract_PATH(void)
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
	if (environ[i] == NULL)
		return (NULL);
	path = ft_strdup(environ[i]);
	trimmed = ft_strtrim(path, "PATH=");
	splited = ft_split(trimmed, ':');
	free(path);
	free(trimmed);
	return (splited);
}

char	*ft_cmd_path(char	**path, char *full_path, char **cmd_tab)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		full_path = malloc(sizeof(char) * (ft_strlen(path[i])
					+ ft_strlen(cmd_tab[0]) + 2));
		if (full_path == NULL)
		{
			ft_free_split(path);
			full_path = NULL;
			break ;
		}
		full_path[0] = '\0';
		ft_strlcat(full_path, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(full_path)
			+ ft_strlen(cmd_tab[0]) + 1);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (full_path);
}

char	*ft_find_cmd(char **cmd_tab)
{
	char	**path;
	char	*full_path;

	full_path = NULL;
	path = ft_extract_PATH();
	if (cmd_tab[0] == NULL || path == NULL)
		return (NULL);
	if (access(cmd_tab[0], X_OK) == 0)
	{
		ft_free_split(path);
		full_path = malloc(sizeof(char) * ft_strlen(cmd_tab[0]) + 1);
		if (full_path == NULL)
		{
			full_path = NULL;
			return (full_path);
		}
		full_path[0] = '\0';
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(cmd_tab[0]) + 1);
		return (full_path);
	}
	full_path = ft_cmd_path(path, full_path, cmd_tab);
	ft_free_split(path);
	return (full_path);
}
