/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:46:48 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/18 16:49:55 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;
	size_t			p;

	p = 0;
	dst = (unsigned char *) s;
	while (p < n)
	{
		dst[p] = (unsigned char)c;
		p++;
	}
	return ((void *)dst);
}
/*
#include <stdio.h>
int main(void)
{
	unsigned char dst[] = "Hello?\n";
	ft_memset(dst, '-', 4);
	printf("%s", dst);
}
*/
