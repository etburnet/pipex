/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:16:21 by eburnet           #+#    #+#             */
/*   Updated: 2024/04/12 15:47:21 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fd1;
	int	fd2;
	int	tempfd;
	int	i;

/* 	if (argc == 6 && argv[1] == "here_doc")
	{
		ft_here_doc();
	} */
	if (argc > 4)
	{
		fd1 = open(argv[1], O_RDWR);
		if (fd1 < 0)
		{
			perror("no such file or directory:");
			return (0);
		}	
		tempfd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644); //
		if (ft_execute(argv[2], fd1, tempfd) == 0) //
		{
			unlink("temp");
			return (0);
		}
		i = 3;
		while (i < argc - 2)
		{
			tempfd = open("temp", O_RDWR); //
			if (ft_execute(argv[i], tempfd, -2) == 0) //
			{
				unlink("temp");
				return (0);
			}
			fd1 = open("temp", O_RDWR | O_TRUNC);
			fd2 = open("tempX", O_RDWR);
			if (ft_move_file(fd1, fd2) == 1)
			{
				unlink("temp");
				unlink("tempX");
				return (0);
			}
			i++;
			unlink("tempX");
		}
		fd2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		tempfd = open("temp", O_RDWR); //
		if (ft_execute(argv[argc - 2], tempfd, fd2) == 0) //
		{
			unlink("temp");
			unlink(argv[argc - 1]);
			return (0);
		}
		ft_close(&fd1, &fd2);
		close(tempfd);
		unlink("temp");
		return (1);
	}
	perror("There is less than 4 args");
	return (0);
}




/* 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// Fonction d'exécution qui fork pour faire son travail
void execute_commande(char *commande) {
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	} else if (pid == 0) { // Processus enfant
		// Exécuter la commande
		execlp(commande, commande, NULL);
		// Si execlp retourne, une erreur s'est produite
		perror("execlp");
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	int i;
	int status;
	pid_t pid;

	i = 1;
	while (argv[i])
		execute_commande(argv[i]);

	// Attendre la fin de tous les processus enfants
	while ((pid = waitpid(-1, &status, 0)) != -1)
	{
		if (WIFEXITED(status))
			printf("Le processus enfant %d s'est terminé avec le code de sortie %d\n", pid, WEXITSTATUS(status));
		else
			printf("Le processus enfant %d s'est terminé de manière anormale\n", pid);
	}
	return 0;
}
 */