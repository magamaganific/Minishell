/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:14:14 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:14:16 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char *line, char *delim)
{
	if (!ft_strncmp(line, delim, ft_strlen(delim))
		&& ft_strlen(line) == ft_strlen(delim))
		return (1);
	return (0);
}

static void	write_heredoc(t_exec_unit *unit, int i, char **my_envp,
	int j)
{
	int		fd_tmp;
	char	*line;
	t_token	*current;

	current = go_to_token(unit, j, i);
	fd_tmp = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_tmp < 0)
		return (perror("minishell"));
	while (!(current->value[0] == '<'))
		current = current->next;
	while (1)
	{
		signal(SIGINT, ft_handle_int_heredoc);
		line = readline("> ");
		if (!line || g_signal.sig == 3)
			break ;
		if (is_delimiter(line, current->next->value))
		{
			free(line);
			break ;
		}
		write_fd(fd_tmp, line);
	}
	return (close(fd_tmp), free_token_list(unit[0].start)
		, exit_heredoc(&my_envp, &unit));
}

int	handle_heredoc(t_exec_unit *unit, int i, char **my_envp, int j)
{
	int			fd_tmp;
	int			status;
	pid_t		pid;

	pid = fork();
	status = 0;
	if (pid == -1)
		return (-1);
	if (pid == 0)
		write_heredoc(unit, i, my_envp, j);
	signal(SIGINT, ft_handle_int_in_p);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	handle_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal.ret = 130;
		return (-1);
	}
	fd_tmp = open("/tmp/.heredoc_tmp", O_RDONLY);
	if (fd_tmp < 0)
		perror("minishell");
	return (fd_tmp);
}

static int	open_input_file(char *filename)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd_in);
}

int	save_input(t_exec_unit *unit, int i, char **my_envp, int j)
{
	t_token	*current;

	current = go_to_token(unit, j, i);
	if (!current)
		return (0);
	if (!current->next)
	{
		error_syntax("newline");
		return (-1);
	}
	if (is_invalid_redirect(current->next->value))
	{
		error_syntax(unit[i].start->next->value);
		return (-1);
	}
	if (!ft_strncmp(current->value, "<<", 2))
		return (handle_heredoc(unit, i, my_envp, j));
	if (!ft_strncmp(current->value, "<", 1))
		return (open_input_file(current->next->value));
	return (-1);
}
