/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:54:56 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/08 07:55:01 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p1;
	size_t			i;

	p1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p1[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
