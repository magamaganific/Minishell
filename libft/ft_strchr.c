/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:50:18 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 15:58:33 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (*s == (char) c)
		return ((char *)s);
	if (!c)
		return ((char *)s);
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	const char s[] = "Dabale arroz a la zorra el abad..";
	int c = 'b';

	printf("%s", ft_strchr(s,c));
}
*/
