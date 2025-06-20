/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:54:27 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/08 13:54:28 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
