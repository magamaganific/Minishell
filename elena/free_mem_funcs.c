/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:52:26 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/12 10:52:28 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_zones(t_zone *zone)
{
	t_zone	*tmp;

	while (zone)
	{
		tmp = zone->next;
		free(zone);
		zone = tmp;
	}
}

void	free_token_list(t_token *command)
{
	t_token	*tmp;

	while (command)
	{
		tmp = command->next;
		free(command->value);
		free_zones(command->zones);
		free(command);
		command = tmp;
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_exec_units(t_exec_unit *units)
{
	int	i;

	if (!units)
		return ;
	i = 0;
	while (units[i].start)
	{
		i++;
	}
	free(units);
}
