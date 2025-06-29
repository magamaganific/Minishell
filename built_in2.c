/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:35:36 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/26 18:35:37 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_exec_unit *units)
{
	if (units->fdin != 0)
		close(units->fdin);
	if (units->fdout != 1)
		close(units->fdout);
}

int	built_in_pwd(t_exec_unit *units)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"), 1);
	while (pwd[i])
	{
		write(units->fdout, &pwd[i], 1);
		i++;
	}
	write(units->fdout, "\n", 1);
	free(pwd);
	return (1);
}

int	built_in_echo(t_exec_unit *units)
{
	t_token	*curr;
	int		endline;

	curr = units->start;
	endline = 1;
	if (curr && curr->value && !ft_strncmp(curr->value, "echo", 5))
		curr = curr->next;
	if (curr && !ft_strncmp(curr->value, "-n", 3))
	{
		endline = 0;
		curr = curr->next;
	}
	while (curr && !is_redirection(curr))
	{
		write(units->fdout, curr->value, ft_strlen(curr->value));
		if (curr->next)
			write(units->fdout, " ", 1);
		curr = curr->next;
	}
	if (endline)
		write(units->fdout, "\n", 1);
	return (1);
}

int	built_in_env(t_exec_unit *units, char ***my_envp)
{
	int	i;

	i = 0;
	while ((*my_envp)[i])
	{
		if (ft_strchr((*my_envp)[i], '='))
		{
			ft_putstr_fd((*my_envp)[i], units->fdout);
			write(units->fdout, "\n", 1);
		}
		i++;
	}
	return (1);
}
