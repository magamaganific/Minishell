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
	free_env(*my_envp);
	free_exec_units(*units);
	exit(127);
}

void	handle_child_signals(void)
{
	signal(SIGQUIT, ft_handle_quit);
	signal(SIGINT, ft_handle_int_in_p);
}
