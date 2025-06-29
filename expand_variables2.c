/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:53:57 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/25 16:53:58 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_token(char *value, char s)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == s)
			return (i);
		i++;
	}
	return (0);
}

int	not_in_zones(int i, t_zone *zone)
{
	while (zone)
	{
		if (i >= zone->start && i <= zone->end)
			return (0);
		zone = zone->next;
	}
	return (1);
}

char	**add_variable(char *addition, char **my_envp)
{
	int		num_strings;
	int		i;
	char	**new_envp;

	num_strings = count_strings(my_envp);
	new_envp = malloc(sizeof(char *) * (num_strings + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < num_strings)
	{
		new_envp[i] = ft_strdup(my_envp[i]);
		if (!new_envp[i])
		{
			free_env(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = ft_strdup(addition);
	new_envp[i + 1] = NULL;
	free_env(my_envp);
	return (new_envp);
}

int	add_variables_to_envp(t_token *command, char ***my_envp)
{
	int		pos;
	char	*addition;
	char	**new_envp;

	pos = in_token(command->value, '=');
	if (pos && !command->next && not_in_zones(pos, command->zones))
	{
		addition = ft_strtrim(command->value, "\t\n\v\f\r ");
		if (!addition)
			return (1);
		new_envp = add_variable(addition, *my_envp);
		if (!new_envp)
		{
			free(addition);
			return (1);
		}
		*my_envp = new_envp;
		free(addition);
		return (1);
	}
	return (0);
}

char	*my_get_envp(char *variable, char **my_envp)
{
	int		i;
	size_t	len;
	char	*replacement;

	i = 0;
	len = ft_strlen(variable);
	while (my_envp[i])
	{
		if (!ft_strncmp(variable, my_envp[i], len)
			&& my_envp[i][len] == '=')
		{
			replacement = ft_substr(my_envp[i], len + 1,
					ft_strlen(my_envp[i]) - len - 1);
			return (replacement);
		}
		i++;
	}
	replacement = ft_strdup("");
	return (replacement);
}
