/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:54:37 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/09 14:54:39 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	word_counter(char *s, char sep)
{
	unsigned int	in_word;
	unsigned int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (!in_word && *s != sep)
		{
			in_word = 1;
			count++;
		}
		if (in_word && *s == sep)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*extract_word(char *s, char sep)
{
	int		k;
	char	*word;

	k = 0;
	while (s[k] && s[k] != sep)
		k++;
	word = (char *)malloc(k + 1);
	if (!word)
		return (NULL);
	k = 0;
	while (s[k] && s[k] != sep)
	{
		word[k] = s[k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

static void	cleanup_array(char **arr)
{
	int	index;

	index = 0;
	while (arr[index])
		free(arr[index++]);
	free(arr);
}

static int	populate_array(const char *s, char sep, char **arr)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != sep)
		{
			arr[j] = extract_word((char *)s + i, sep);
			if (!arr[j])
				return (0);
			j++;
			while (s[i] && s[i] != sep)
				i++;
			continue ;
		}
		i++;
	}
	return (1);
}

char	**ft_split(const char *s, char sep)
{
	char			**result;
	unsigned int	num_words;

	if (!s)
		return (NULL);
	num_words = word_counter((char *)s, sep);
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[num_words] = NULL;
	if (!populate_array(s, sep, result))
	{
		cleanup_array(result);
		return (NULL);
	}
	return (result);
}
