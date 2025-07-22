/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:19:17 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/23 13:19:18 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *str, int start, int end)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = extract_token_value(str, start, end);
	tok->zones = NULL;
	tok->next = NULL;
	return (tok);
}

int	process_quoted_zone(char *str, int *i, t_token *tok)
{
	char	quote;
	int		start;
	int		expandable;

	quote = str[*i];
	start = *i;
	expandable = 0;
	if (quote == '"')
		expandable = 1;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
	{
		add_zone(tok, create_zone(start, *i, expandable));
		(*i)++;
	}
	return (*i);
}

int	find_token_end(char *str, int i)
{
	char	quote;

	while (str[i] && str[i] != ' ' && !is_metachar(str[i]))
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

void	append_token(t_token **head, t_token *new_tok)
{
	t_token	*curr;

	if (!*head)
		*head = new_tok;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_tok;
	}
}

void	write_fd(int fd_tmp, char *line)
{
	write(fd_tmp, line, ft_strlen(line));
	write(fd_tmp, "\n", 1);
	free(line);
}
