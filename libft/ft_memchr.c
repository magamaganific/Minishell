/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:17:35 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 16:47:22 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*loc;
	size_t			p;

	loc = (unsigned char *) s;
	p = 0;
	while (p < n)
	{
		if (loc[p] == (unsigned char)c)
			return ((void *) &loc[p]);
		p++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{
	const char s[] = "Dabale arroz a la zorra el abad..";
	int c = 'l';
	char *res;
	size_t n = 20;

	res = ft_memchr(s,c,n);
	printf("%c found at %ld:\n", c, res - s);
	printf("%s --->> %s", s, res);
}
*/
