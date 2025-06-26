/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:27:04 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/26 11:27:09 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(long nbr)
{
	int	digits;

	digits = 0;
	if (nbr < 0)
	{
		digits ++;
		nbr = -nbr;
	}
	if (nbr == 0)
		digits++;
	while (nbr != 0)
	{
		nbr /= 10;
		digits++;
	}
	return (digits);
}

char	ft_putnum(int n)
{
	char	*dig;

	dig = "0123456789";
	return (dig[n]);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		c;
	int		len;
	long	nbr;

	c = 0;
	nbr = n;
	len = num_len(nbr);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	res[c] = '0';
	if (nbr < 0)
	{
		res[c] = '-';
		nbr = -nbr;
	}
	c = len - 1;
	while (c >= 0 && nbr)
	{
		res[c] = ft_putnum(nbr % 10);
		nbr = nbr / 10;
		c--;
	}
	return (res);
}
/*
#include <stdio.h>
#include <limits.h>
int main(void)
{
	int n = INT_MAX + 1;
	char *num;
	int	c;
	
	num = ft_itoa(n);
	printf("itoa result =\n");
	while (num[c])
	{
		printf("%c", num[c]);
		c++;
	}
} 
*/
