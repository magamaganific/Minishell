/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:47:52 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 16:55:24 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*f1;
	const unsigned char	*f2;
	size_t				res;

	f1 = (const unsigned char *) s1;
	f2 = (const unsigned char *) s2;
	res = 0;
	if (n == 0)
		return (0);
	while (*f1 == *f2 && n > 1)
	{
		f1++;
		f2++;
		n--;
	}
	if (*f1 != *f2)
		res = *f1 - *f2;
	return (res);
}
/*
#include <stdio.h>
int main(void)
{
	const char s1[] = "AAAAA";
	const char s2[] = "AAAaA";
	size_t n = 2;
	int res;

	res = ft_memcmp(s1, s2, n);
	printf("%d", res);
}
*/
