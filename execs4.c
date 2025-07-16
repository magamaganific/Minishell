/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:54:42 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:54:43 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	setup_pipe_and_fork(int *fd, int has_next)
{
	pid_t	pid;

	if (has_next)
	{
		if (pipe(fd) == -1)
		{
			perror("minishell: pipe");
			return (-1);
		}
	}
	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	return (pid);
}

static void	setup_child_io(t_exec_unit *unit, int *fd, int has_next,
			int prev_fd)
{
	if (unit->fdin != STDIN_FILENO)
	{
		dup2(unit->fdin, STDIN_FILENO);
		close(unit->fdin);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (unit->fdout != STDOUT_FILENO)
	{
		dup2(unit->fdout, STDOUT_FILENO);
		close(unit->fdout);
	}
	else if (has_next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static void	handle_parent_pipe(int *fd, int *prev_fd, int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

void	execute_units_with_pipes(t_exec_unit *units, char **my_envp)
{
	int		i;
	int		status;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (units[i].start)
	{
		pid = setup_pipe_and_fork(fd, units[i + 1].start != NULL);
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			setup_child_io(&units[i], fd, units[i + 1].start != NULL, prev_fd);
			exec_simple_command(units[i].start, my_envp);
			free_env(my_envp);
			free_exec_units(units);
			exit(127);
		}
		handle_parent_pipe(fd, &prev_fd, units[i + 1].start != NULL);
		i++;
	}
	while (wait(&status) > 0)
		g_signal.ret = WEXITSTATUS(status);
}

void	exec_simple_command(t_token *start, char **my_envp)
{
	char	**argv;
	char	*path;

	argv = build_argv(start);
	if (!argv || !argv[0])
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return ;
	}
	path = find_command_path(argv[0], my_envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_split(argv);
		free(path);
		free_token_list(start);
		return ;
	}
	execve(path, argv, my_envp);
	perror("minishell");
	free_split(argv);
	free(path);
	free_token_list(start);
	return ;
}
