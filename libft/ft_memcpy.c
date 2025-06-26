/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:23:35 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/18 18:03:39 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sc;
	size_t			p;

	p = 0;
	dst = (unsigned char *) dest;
	sc = (unsigned char *) src;
	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	while (p < n)
	{
		dst[p] = sc[p];
		p++;
	}
	return ((void *)dst);
}
/*
#include <stdio.h>
int main(void)
{
	unsigned char dest[] = "Hello?\n";
	unsigned char src[] = "Bye";
	ft_memcpy(dest, src, 3);
	printf("%s", dest);
}
*/
