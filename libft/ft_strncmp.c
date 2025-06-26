/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:05:50 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 16:17:07 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;

	c = 0;
	while (((s1[c] || s2[c]) && c < n))
	{
		if ((unsigned char)s1[c] != (unsigned char)s2[c])
			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
		c++;
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	const char s1[] = "AAAAA";
	const char s2[] = "AAAaA";
	size_t n = 2;
	int res;

	res = ft_strncmp(s1, s2, n);
	printf("%d", res);
}
*/
