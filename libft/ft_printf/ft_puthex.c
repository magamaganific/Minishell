/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:18:56 by mfornovi          #+#    #+#             */
/*   Updated: 2024/10/15 10:36:34 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long long n, int c)
{
	int		len;
	char	hex_digit;
	char	hex_cap;

	len = 0;
	hex_digit = "0123456789abcdef"[n % 16];
	hex_cap = "0123456789ABCDEF"[n % 16];
	if (n >= 16)
		len += ft_puthex(n / 16, c);
	if (!c)
		len += ft_putchar(hex_digit);
	else
		len += ft_putchar(hex_cap);
	return (len);
}
