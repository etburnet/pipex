/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:22:10 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/19 10:23:23 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

extern char		**environ;
int				ft_ex_here(char *cmd_path, char **cmd_tab, int fd2, char *limiter);
int				ft_execute(char **argv, int argc, int fd1, int fd2);
void			ft_free_split(char	**tab);
int				ft_free_all(char ***cmd_tab, int *fd1, int *fd2, char *error);
char			*ft_find_cmd(char **cmd_tab);
int				ft_copy_file(int fd1, int fd2);
int				ft_unlink_return(int argc, char *argv[]);
void			ft_close(int *fd1, int *fd2);
int				ft_here_doc(int argc, char *argv[]);

#endif