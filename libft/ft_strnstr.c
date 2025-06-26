/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:56:40 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/25 10:35:16 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	c;
	size_t	n;
	size_t	lil;

	n = 0;
	c = 0;
	lil = ft_strlen(little);
	if (len == 0 || big == little)
	{
		if (len >= lil)
			return ((char *) big);
		return (0);
	}
	while (big[c] != '\0' && c <= len)
	{
		n = 0;
		while (big [c + n] == little[n] && little[n] != '\0'
			&& big[c + n] != '\0' && c + n < len)
			n++;
		if (n == lil)
			return ((char *) big + c);
		c++;
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	char big[] = "Zaragoza y sus recuerdos";
	char little[] = "sus";
	size_t	len = 12;

	printf ("%s", ft_strnstr(big, little, len));
}
*/
