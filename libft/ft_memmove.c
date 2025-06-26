/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:33:31 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/18 18:03:02 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dst;
	char	*sc;

	if (!dest && !src)
		return (NULL);
	dst = (char *)dest;
	sc = (char *)src;
	if (dst < sc)
		dst = ft_memcpy(dest, src, n);
	else
	{
		dst = (char *)dest;
		sc = (char *)src;
		while (n--)
			dst[n] = sc[n];
	}
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
	unsigned char dst[] = "Hello?, I am Maria.";
	unsigned char src[] = "Hello?";
	ft_memmove(dst, src, 6);
	printf("%s", dst);
}
*/
