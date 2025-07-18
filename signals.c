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
	int	fd[2];

	(void)sig;
	if (pipe(fd) < 0)
		perror("Pipe:");
	dup2(fd[0], STDIN_FILENO);
	write(fd[1], "\n\n", 2);
	close(fd[0]);
	close(fd[1]);
	g_signal.ret = 130;
	return ;
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

void	ft_handle_sigquit(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
	exit(0);
}
