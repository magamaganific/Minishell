/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:42:33 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/12 10:42:34 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_metachar(char *cleaned, int *i, t_token **tokens)
{
	t_token	*tok;
	int		start;

	start = *i;
	(*i)++;
	if ((cleaned[start] == '<' || cleaned[start] == '>')
		&& cleaned[*i] == cleaned[start])
		(*i)++;
	tok = new_token(cleaned, start, *i);
	if (!tok)
		return (-1);
	append_token(tokens, tok);
	return (0);
}

static int	tokenize_regular(char *cleaned, int *i, t_token **tokens)
{
	t_token	*tok;
	int		start;
	int		end;

	start = *i;
	end = find_token_end(cleaned, *i);
	tok = new_token(cleaned, start, end);
	if (!tok)
		return (-1);
	while (*i < end)
	{
		if (is_quote(cleaned[*i]))
			process_quoted_zone(cleaned, i, tok);
		else
			(*i)++;
	}
	append_token(tokens, tok);
	return (0);
}

t_token	*tokenizer(char *cleaned)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (cleaned[i] == ' ')
		i++;
	if (!cleaned[i])
		return (NULL);
	while (cleaned[i])
	{
		while (cleaned[i] == ' ')
			i++;
		if (!cleaned[i])
			break ;
		if (is_metachar(cleaned[i]))
		{
			if (tokenize_metachar(cleaned, &i, &tokens) == -1)
				return (NULL);
			continue ;
		}
		if (tokenize_regular(cleaned, &i, &tokens) == -1)
			return (NULL);
	}
	return (tokens);
}

static void	relativize_token_zones(t_token *curr, char *cleaned, char *base)
{
	t_zone	*zone;
	char	*pos;
	int		diff;

	pos = ft_strnstr(cleaned, curr->value, ft_strlen(base));
	if (!pos)
		return ;
	diff = pos - base;
	zone = curr->zones;
	while (zone)
	{
		zone->start = zone->start - diff;
		zone->end = zone->end - diff;
		zone = zone->next;
	}
}

void	relativize_zones(t_token *tokens, char *cleaned)
{
	t_token	*curr;
	char	*base;

	curr = tokens;
	base = cleaned;
	while (curr)
	{
		relativize_token_zones(curr, cleaned, base);
		curr = curr->next;
	}
}
