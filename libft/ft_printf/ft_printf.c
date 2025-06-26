/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:06:40 by mfornovi          #+#    #+#             */
/*   Updated: 2024/10/21 11:42:39 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	identif_conv(const char conv, va_list args)
{
	int	len;

	len = 0;
	if (conv == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (conv == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (conv == 'd' || conv == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (conv == 'p')
		len += ft_putptr(va_arg(args, void *));
	else if (conv == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (conv == 'x')
		len += ft_puthex(va_arg(args, unsigned int), 0);
	else if (conv == 'X')
		len += ft_puthex(va_arg(args, unsigned int), 1);
	else if (conv == '%')
		len += ft_putchar('%');
	else
	{
		len += ft_putchar('%');
		len += ft_putchar(conv);
	}
	return (len);
}

int	ft_printf(char const *input, ...)
{
	int			i;
	int			len;
	va_list		args;

	i = 0;
	len = 0;
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1] == '\0')
			return (-1);
		if (input[i] == '%')
		{
			len += identif_conv(input[i + 1], args);
			i++;
		}
		else
			len += ft_putchar(input[i]);
		i++;
	}
	va_end(args);
	return (len);
}
/*
#include <stdio.h>
int main(void)
{
	int	c = 'M';
	char const s[15]= "Idk really tho";
	int	n = 1300135;
	char const s2[4] = "LOL";
	int	hex = 6356;
	unsigned int n2 = 10;
	int	num;

	num = ft_printf("\n%c %s %d %i %s\n%u %x %X %p\n\n%%%%%  a",
	c, s, n, n, s2, n2, hex, hex, NULL);
	printf("\n%d\n", num);
}
*/
