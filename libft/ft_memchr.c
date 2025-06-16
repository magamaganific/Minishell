/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:58:41 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/08 07:58:43 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p1;
	size_t	i;

	p1 = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)p1[i] == (unsigned char)c)
			return (&p1[i]);
		i++;
	}
	return (NULL);
}
