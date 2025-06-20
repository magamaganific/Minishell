/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:54:51 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/09 14:54:54 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	potential_memory(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*special_cases(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*p1;
	int		len;

	if (n == 0 || n == -2147483648)
		return (special_cases(n));
	len = potential_memory(n);
	p1 = malloc((len + 1) * sizeof(char));
	if (!p1)
		return (NULL);
	if (n < 0)
	{
		p1[0] = '-';
		n = -n;
	}
	p1[len] = '\0';
	len--;
	while (n > 0)
	{
		p1[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (p1);
}
