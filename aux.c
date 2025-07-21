/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:29:10 by elengarc          #+#    #+#             */
/*   Updated: 2025/07/17 15:29:11 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_child(char	***my_envp, t_exec_unit **units)
{
	close_fds(*units);
	free_env(*my_envp);
	free_token_list(units[0]->start);
	free_exec_units(units[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
	exit(127);
}

void	exit_heredoc(char	***my_envp, t_exec_unit **units)
{
	close_fds(*units);
	free_env(*my_envp);
	free_exec_units(*units);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
	exit(0);
}

void	handle_child_signals(void)
{
	signal(SIGQUIT, ft_handle_quit);
	signal(SIGINT, ft_handle_int_in_p);
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_int);
	signal(SIGTSTP, SIG_IGN);
}
