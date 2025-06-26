/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:51:04 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/18 17:22:56 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dst;
	size_t			p;

	p = 0;
	dst = (unsigned char *) s;
	while (p < n)
	{
		dst[p] = '\0';
		p++;
	}
}
/*
#include <stdio.h>
int main(void)
{
        int dst[4] = {1,2,3,4};
        ft_bzero(dst, 5);
	int i;
	i = 0;
	while (i < 4)
	{
		printf("%d", dst[i]);
		i++;
	}
}
*/
