/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:44:41 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:44:42 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_exec_units(t_token *command)
{
	int		count;
	t_token	*node;

	count = 1;
	node = command;
	while (node)
	{
		if (!ft_strncmp(node->value, "|", 2))
			count++;
		node = node->next;
	}
	return (count);
}

static void	init_exec_unit(t_exec_unit *unit, t_token *start)
{
	unit->start = start;
	unit->fdin = 0;
	unit->fdout = 1;
	unit->has_pipe_after = 0;
}

static t_token	*process_until_pipe(t_token *current, t_exec_unit *unit)
{
	t_token	*next;

	while (current && ft_strncmp(current->value, "|", 2))
		current = current->next;
	if (current && !ft_strncmp(current->value, "|", 2))
	{
		unit->has_pipe_after = 1;
		next = current->next;
		current = NULL;
		return (next);
	}
	return (NULL);
}

t_exec_unit	*split_into_exec_units(t_token *command)
{
	t_exec_unit	*units;
	t_token		*current;
	int			i;
	int			n_units;

	i = 0;
	n_units = count_exec_units(command);
	units = malloc(sizeof(t_exec_unit) * (n_units + 1));
	if (!units)
		return (NULL);
	current = command;
	while (current)
	{
		init_exec_unit(&units[i], current);
		current = process_until_pipe(current, &units[i]);
		i++;
	}
	units[i].start = NULL;
	return (units);
}
