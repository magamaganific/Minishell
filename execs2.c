/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:49:24 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:49:25 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_output_redir(t_token *current, int *fdout)
{
	*fdout = save_output(current);
	if (*fdout == -1)
		return (-1);
	return (0);
}

static int	handle_input_redir(t_exec_unit *unit, int i, char **my_envp)
{
	unit[i].fdin = save_input(unit, i, my_envp);
	if (unit[i].fdin == -1)
		return (-1);
	return (0);
}

int	handle_redirections(t_exec_unit *unit, int i, char **my_envp)
{
	t_token	*current;

	current = unit->start;
	unit[i].fdin = 0;
	unit[i].fdout = 1;
	while (current && ft_strncmp(current->value, "|", 2))
	{
		if (!ft_strncmp(current->value, ">", 2)
			|| !ft_strncmp(current->value, ">>", 3))
		{
			if (handle_output_redir(current, &unit[i].fdout) == -1)
				return (-1);
		}
		else if (!ft_strncmp(current->value, "<", 2)
			|| !ft_strncmp(current->value, "<<", 3))
		{
			if (handle_input_redir(unit, i, my_envp) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static int	is_argument_token(t_token *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token->value, "|", 2))
		return (0);
	if (!ft_strncmp(token->value, ">", 2))
		return (0);
	if (!ft_strncmp(token->value, ">>", 3))
		return (0);
	if (!ft_strncmp(token->value, "<", 2))
		return (0);
	if (!ft_strncmp(token->value, "<<", 3))
		return (0);
	return (1);
}

int	count_args(t_token *start)
{
	int	count;
	int	i;

	count = 0;
	while (start && is_argument_token(start))
	{
		count++;
		i = 0;
		while (start->value[i])
		{
			if (start->value[i] == ' ')
				count++;
			i++;
		}
		start = start->next;
	}
	return (count);
}
