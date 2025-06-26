/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:02:49 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/26 14:02:53 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	makestr(long n, int fd)
{
	char	digit;

	if (n > 9)
	{
		makestr(n / 10, fd);
		makestr(n % 10, fd);
	}
	else
	{
		digit = n + '0';
		write(fd, &digit, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	makestr(nbr, fd);
}
/*
#include <stdio.h>
#include <limits.h>
int main(void)
{
	int n = 121;
	
	ft_putnbr_fd(n, 1);
} 
*/
