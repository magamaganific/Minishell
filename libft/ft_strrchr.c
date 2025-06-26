/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:59:17 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 16:05:34 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	count;

	count = ft_strlen(s);
	while (count > 0)
	{
		if (s[count] == (char)c)
			return ((char *)&s[count]);
		count--;
	}
	if (s[count] == (char)c)
		return ((char *)&s[count]);
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	const char s[] = "Dabale arroz a la zorra el abad..";
	int c = 'e';

	printf("%s", ft_strrchr(s,c));
}
*/
