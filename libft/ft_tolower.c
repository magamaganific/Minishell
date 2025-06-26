/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:44:58 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 15:49:05 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/*
#include <stdio.h>
int main(void)
{
	int c = 'A';
	int r;

	r = ft_tolower(c);
	printf("before: %c\n", c);
	printf("after: %c\n", r);
}
*/
