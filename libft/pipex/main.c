/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:06:31 by mfornovi          #+#    #+#             */
/*   Updated: 2025/03/10 09:06:34 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(int *pipefd, int in_fd, char **av, char **env)
{
	char	**args1;

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(pipefd[1]);
	close(in_fd);
	args1 = ft_mkargs(av[2], env);
	execve(args1[0], args1, env);
	ft_freer(args1);
	perror("execve");
	exit(127);
}

void	child2(int *pipefd, int in_fd, char **av, char **env)
{
	char	**args2;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(pipefd[0]);
	close(in_fd);
	args2 = ft_mkargs(av[3], env);
	execve(args2[0], args2, env);
	ft_freer(args2);
	perror("execve");
	exit(127);
}

void	ft_forking(int *pipefd, int in_fd, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		ft_errorman("fork");
	if (pid1 == 0)
		child1(pipefd, in_fd, av, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_errorman("fork");
	if (pid2 == 0)
		child2(pipefd, in_fd, av, env);
	ft_closer(in_fd, pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	int		out_fd;
	int		in_fd;

	in_fd = 0;
	if (ac != 5)
	{
		ft_printf("Invalid input: Expected input:");
		ft_printf("	<infile> <\"cmd1\"> <\"cmd2\"> <outfile>\n");
		return (0);
	}
	out_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (access(av[1], R_OK) != -1)
	{
		in_fd = open(av[1], O_RDONLY, 0644);
		dup2(in_fd, STDIN_FILENO);
	}
	if (pipe(pipefd) == -1)
		ft_errorman("pipe");
	ft_forking(pipefd, in_fd, av, env);
	return (0);
}
