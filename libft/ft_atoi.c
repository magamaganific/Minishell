/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:24:57 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/19 17:53:46 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sgn;
	int	dig;
	int	num;

	sgn = 1;
	dig = 0;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sgn = -sgn;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		dig = *nptr - '0';
		num = num * 10 + dig;
		nptr++;
	}
	num = num * sgn;
	return (num);
}
/*
#include <stdio.h>
#include <stdlib.h>

int atoi(const char *str);

int main(void)
{
	int val;
	int val2;
	const char str[] = "-123";
	const char str2[] = "-123";

	val = ft_atoi(str);
	val2 = atoi(str2);

	printf("my atoi = %d\n", val);
	printf("atoi = %d\n", val2);
}
*/
