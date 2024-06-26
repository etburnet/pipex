/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:06:45 by eburnet           #+#    #+#             */
/*   Updated: 2024/06/14 15:22:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_extract_path(void)
{
	char	*path;
	char	*trimmed;
	char	**splited;
	int		i;

	i = 0;
	if (environ == NULL || environ[i] == NULL)
		return (NULL);
	while (environ[i++] != NULL)
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break ;
	if (environ[i] == NULL)
		return (NULL);
	path = ft_strdup(environ[i]);
	if (path == NULL)
		return (NULL);
	trimmed = ft_strtrim(path, "PATH=");
	free(path);
	if (trimmed == NULL)
		return (NULL);
	splited = ft_split(trimmed, ':');
	free(trimmed);
	if (splited == NULL)
		return (NULL);
	return (splited);
}

char	*ft_cmd_path(char **path, char *full_path, char **cmd_tab)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		full_path = malloc(sizeof(char) * (ft_strlen(path[i])
					+ ft_strlen(cmd_tab[0]) + 2));
		if (full_path == NULL)
			return (ft_free_split(path), NULL);
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
	if (full_path == NULL)
		ft_free_split(path);
	return (full_path);
}

char	*ft_find_cmd(char **cmd_tab)
{
	char	**path;
	char	*full_path;

	full_path = NULL;
	path = NULL;
	path = ft_extract_path();
	if (path == NULL)
		return (NULL);
	if (cmd_tab[0] == NULL)
		return (ft_free_split(path), NULL);
	if (access(cmd_tab[0], X_OK) == 0)
	{
		ft_free_split(path);
		full_path = malloc(sizeof(char) * ft_strlen(cmd_tab[0]) + 1);
		if (full_path == NULL)
			return (NULL);
		full_path[0] = '\0';
		ft_strlcat(full_path, cmd_tab[0], ft_strlen(cmd_tab[0]) + 1);
		return (full_path);
	}
	full_path = ft_cmd_path(path, full_path, cmd_tab);
	if (full_path == NULL)
		return (NULL);
	ft_free_split(path);
	return (full_path);
}
