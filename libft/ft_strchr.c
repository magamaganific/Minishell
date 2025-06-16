/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:58:08 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/08 07:58:09 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if ((char)p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&p[i]);
	return (NULL);
}
