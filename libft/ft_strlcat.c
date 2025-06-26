/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:16:07 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 15:35:41 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (len_d >= size)
		len_d = size;
	if (len_d == size)
		return (len_s + size);
	if (len_s < size - len_d)
		ft_memcpy(dst + len_d, src, len_s + 1);
	else
	{
		ft_memcpy(dst + len_d, src, size - len_d - 1);
		dst[size - 1] = '\0';
	}
	return (len_d + len_s);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char src[]= ", Barra vieja";
	char dst[20]= "lol";
	size_t size = 2;

	printf("%zu\n", ft_strlcat(dst, src, size));
	printf("%s\n", dst);
}
*/
