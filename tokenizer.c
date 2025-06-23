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

/*
void	print_zones(t_zone *zones, char *token_value)
{
	while (zones)
	{
		printf("\t[ZONE] start: %d, end: %d, expandable: %d\n",
			zones->start, zones->end, zones->expandable);
		printf("\t       --> content: \"");
		for (int i = zones->start; i < zones->end+1; i++)
			putchar(token_value[i]);
		printf("\"\n");
		zones = zones->next;
	}
}

void	print_tokens(t_token *tokens)
{
	int index = 0;
	while (tokens)
	{
		printf("[TOKEN %d] value: \"%s\"\n", index, tokens->value);
		if (tokens->zones)
			print_zones(tokens->zones, tokens->value);
		tokens = tokens->next;
		index++;
	}
}

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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*p1;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	p1 = malloc(len + 1);
	if (!p1)
		return (NULL);
	while (i < len)
	{
		p1[i] = s[i];
		i++;
	}
	p1[i] = '\0';
	return (p1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}


char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < n)
	{
		j = 0;
		while (little[j] && (i + j) < n && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

int main(void)
{
	const char *test_cases[] = {
		// Caso de prueba original complejo
		"echo \"Hola que tal\"$USER'$USER' | grep 'Ele' > outfile >>hola \"lets'gooo' >ahora no redirige\" > \"pero ahora sii\"",

		// Casos más complicados
		"echo \"$USER's profile\" >>file | cat <'data input'",
		"echo \"Inicio\"$MIDDLE'Fin'|grep \"pattern>'a'\" >> salida",
		"cmd1 < input1 | cmd2 \"text$VAR>'a'\" > 'output final'",
		"echo \"double'quoted'word\" 'single\"quoted\"part' | tee result",
		"echo 'quote>\"test\"' \"quote<'test'\" | sort > file",
		"ls -l | grep \"Jan 01\" >> log$DATE'tmp'",
		"echo \"$USER\"\"'$USER'\"'$HOME'",
		"echo \"start'$VAR'end\">file",
		"cmd arg1 \">>\" '<<' | another > 'file name with spaces.txt'",
		"echo 'Unmatched quote test > still counts' >>file"
	};

	int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
	for (int i = 0; i < num_cases; i++)
	{
		printf("=======================================================================\n");
		printf("CASO %d:\n%s\n", i + 1, test_cases[i]);
		printf("=======================================================================\n");
		printf ("\n");
		t_token *tokens = tokenizer((char *)test_cases[i]);
		if (!tokens)
		{
			fprintf(stderr, "Error al tokenizar el input");
			continue;
		}
		relativize_zones(tokens, (char *)test_cases[i]);
		print_tokens(tokens);
		free_token_list(tokens);
		printf ("\n\n");
	}
	return (0);
}
*/