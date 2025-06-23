/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:19:01 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/23 13:19:02 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

t_zone	*create_zone(int start, int end, int expandable)
{
	t_zone	*zone;

	zone = malloc(sizeof(t_zone));
	if (!zone)
		return (NULL);
	zone->start = start + 1;
	zone->end = end - 1;
	zone->expandable = expandable;
	zone->next = NULL;
	return (zone);
}

void	add_zone(t_token *token, t_zone *zone)
{
	t_zone	*curr;

	if (!token->zones)
		token->zones = zone;
	else
	{
		curr = token->zones;
		while (curr->next)
			curr = curr->next;
		curr->next = zone;
	}
}

char	*extract_token_value(char *str, int start, int end)
{
	char	*substr;

	substr = ft_substr(str, start, end - start);
	return (substr);
}
