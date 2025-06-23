/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:11:49 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:11:50 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	clean_tokens(t_token *tokens)
{
	t_token	*curr;
	char	*new_value;

	curr = tokens;
	while (curr)
	{
		new_value = remove_quotes(curr->value);
		if (!new_value)
			return ;
		free(curr->value);
		curr->value = new_value;
		curr = curr->next;
	}
}

char	*ft_strjoin_gnl(char *s1, char *s2, size_t len1, size_t len2)
{
	char	*result;
	size_t	i;

	if (!s2 || !s1)
		return (free(s1), s1 = NULL, NULL);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (free(s1), s1 = NULL, NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	free(s1);
	return (result);
}

static void	update_quote_status(char c, int *squote, int *dquote)
{
	if (c == '"' && *squote == 0)
		*dquote = !(*dquote);
	else if (c == '\'' && *dquote == 0)
		*squote = !(*squote);
}

int	check_quotes(char *line)
{
	int	squote;
	int	dquote;
	int	i;

	squote = 0;
	dquote = 0;
	i = 0;
	while (line[i])
	{
		update_quote_status(line[i], &squote, &dquote);
		i++;
	}
	if (squote == 1 || dquote == 1)
		return (0);
	return (1);
}
