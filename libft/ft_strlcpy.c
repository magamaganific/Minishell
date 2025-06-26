/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:05:34 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 14:49:01 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	c;

	c = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (c < (size - 1) && src[c] != '\0')
	{
		dst[c] = src[c];
		c++;
	}
	dst[c] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdio.h>
int main(void)
{
	char src[]= "Barra vieja";
	char dst[40];
	size_t size = 10;

	printf("%zu\n", ft_strlcpy(dst, src + 3, size));
	printf("%s\n", dst);
}
*/
