/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:33:21 by mfornovi          #+#    #+#             */
/*   Updated: 2025/07/07 12:33:29 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_quit(int sig)
{
	printf("Quit (Core dumped)\n");
	(void)sig;
	g_signal.ret = 131;
}

void	ft_handle_int_heredoc(int sig)
{
	int	pipefd[2];

	(void)sig;
	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	dup2(pipefd[0], STDIN_FILENO);
	write(pipefd[1], "\n", 1);
	close(pipefd[0]);
	close(pipefd[1]);
	printf("\n");
	g_signal.ret = 130;
	exit(130);
}

void	ft_handle_int_in_p(int sig)
{
	(void)sig;
	printf("\n");
	g_signal.ret = 130;
}

void	ft_handle_int(int sig)
{
	if (g_signal.ff == 1)
		return ;
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_signal.ret = 130;
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_int);
	signal(SIGTSTP, SIG_IGN);
}
