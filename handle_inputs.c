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

static void	write_heredoc(t_token *node, char *filename)
{
	int		fd_tmp;
	char	*line;

	fd_tmp = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_tmp < 0)
	{
		perror("minishell");
		return ;
	}
	while (1)
	{
		signal(SIGINT, ft_handle_int_heredoc);
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(line, node->next->value))
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		write(fd_tmp, "\n", 1);
		free(line);
	}
	close(fd_tmp);
	return ;
}

int	handle_heredoc(t_token *node)
{
	int			fd_tmp;
	int			status;
	const char	*filename;
	pid_t		pid;

	filename = "/tmp/.heredoc_tmp";
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		write_heredoc(node, (char *)filename);
	signal(SIGINT, ft_handle_int_in_p);
	waitpid(pid, &status, 0);
	fd_tmp = open(filename, O_RDONLY);
	if (fd_tmp < 0)
		perror("minishell");
	g_signal.ret_exit = WEXITSTATUS(status);
	if (g_signal.ret_exit == 130)
		return (-1);
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

int	save_input(t_token *node)
{
	if (!node->next)
	{
		error_syntax("newline");
		return (-1);
	}
	if (is_invalid_redirect(node->next->value))
	{
		error_syntax(node->next->value);
		return (-1);
	}
	if (!ft_strncmp(node->value, "<<", 3))
		return (handle_heredoc(node));
	if (!ft_strncmp(node->value, "<", 2))
		return (open_input_file(node->next->value));
	return (-1);
}
