/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:40:55 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/24 16:41:03 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_variable(t_token *node, int i, int j, char *replacement)
{
	char	*final_value;
	int		len_before;
	int		len_after;
	int		total_len;

	len_before = i;
	len_after = ft_strlen(&node->value[j]);
	total_len = len_before + ft_strlen(replacement) + len_after;
	final_value = malloc(total_len + 1);
	if (!final_value)
		return ;
	ft_strlcpy(final_value, node->value, len_before + 1);
	ft_strlcat(final_value, replacement, total_len + 1);
	ft_strlcat(final_value, &node->value[j], total_len + 1);
	free(node->value);
	node->value = final_value;
}

int	find_variable(t_token *node, int i, char **my_envp)
{
	int		j;
	char	*variable;
	char	*replacement;

	j = i + 1;
	while (node->value[j] && (ft_isalnum(node->value[j])
			|| node->value[j] == '_'))
		j++;
	if (j == i + 1)
		return (i + 1);
	variable = ft_substr(node->value, i + 1, j - i - 1);
	if (!variable)
		return (i + 1);
	replacement = my_get_envp(variable, my_envp);
	if (!replacement)
	{
		free(variable);
		return (i + 1);
	}
	replace_variable(node, i, j, replacement);
	free(variable);
	free(replacement);
	return (i + ft_strlen(replacement));
}

int	is_in_zones(int i, t_zone *zone)
{
	if (zone == NULL)
		return (1);
	while (zone)
	{
		if (zone->expandable == 0 && i >= zone->start && i <= zone->end)
			return (0);
		zone = zone->next;
	}
	return (1);
}

void	extract_variable_name(t_token *node, char **my_envp)
{
	int	i;

	i = 0;
	while (node->value[i])
	{
		if (node->value[i] == '$'
			&& is_in_zones(i, node->zones))
		{
			i = find_variable(node, i, my_envp);
			continue ;
		}
		i++;
	}
}

void	expand_variables(t_token *command, char **my_envp)
{
	t_token	*node;

	node = command;
	while (node)
	{
		extract_variable_name(node, my_envp);
		node = node->next;
	}
}
