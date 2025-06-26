/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:21:47 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/24 13:01:32 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_word(char const *src, int start, int end)
{
	char	*word;
	int		n;

	n = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[n] = src[start];
		n++;
		start++;
	}
	word[n] = 0;
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	n;

	n = 0;
	while (n < count)
	{
		free(strs[n]);
		n++;
	}
	free(strs);
	return (NULL);
}

int	word_count(const char *s, char c)
{
	int	n;
	int	words;

	n = 0;
	words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && n == 0)
		{
			n = 1;
			words++;
		}
		else if (*s == c)
			n = 0;
		s++;
	}
	return (words);
}

static void	initials_var(size_t *n, int *l, int *start_w)
{
	*n = 0;
	*l = 0;
	*start_w = -1;
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	n;
	int		l;
	int		start_w;

	initials_var(&n, &l, &start_w);
	split = (char **)ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	while (n <= ft_strlen(s))
	{
		if (s[n] != c && start_w < 0)
			start_w = n;
		else if ((s[n] == c || n == ft_strlen(s)) && start_w >= 0)
		{
			split[l] = fill_word(s, start_w, n);
			if (!(split[l]))
				return (ft_free(split, l));
			start_w = -1;
			l++;
		}
		n++;
	}
	return (split);
}
/*
#include <stdio.h>
int main(void)
{
	const char s[] = "Mi mama me mima..";
	int c = ' ';
	char **result;

	result = ft_split(s,c);
	
	while (*result)
	{
		printf("%s\n", *result);
		result++;
	}
}
*/
