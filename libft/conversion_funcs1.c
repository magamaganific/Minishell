/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_funcs1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:22:26 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/17 16:22:28 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_num_base(unsigned long n, char *base, size_t len)
{
	if (n >= len)
		ft_put_num_base(n / len, base, len);
	ft_putchar_fd(base[n % len], 1);
}

int	ft_convert_hex_min(va_list *args)
{
	unsigned int	n;
	int				count;

	count = 0;
	n = va_arg(*args, unsigned int);
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_put_num_base(n, "0123456789abcdef", 16);
	while (n)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	ft_convert_hex_max(va_list *args)
{
	unsigned int	n;
	int				count;

	n = va_arg(*args, unsigned int);
	count = 0;
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_put_num_base(n, "0123456789ABCDEF", 16);
	while (n)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	ft_convert_hex_pointer(va_list *args)
{
	void			*ptr;
	unsigned long	n;
	int				count;

	ptr = va_arg(*args, void *);
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	n = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	count = 2;
	ft_put_num_base(n, "0123456789abcdef", 16);
	while (n)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	ft_convert_unsigned(va_list *args)
{
	unsigned int	n;
	int				count;

	count = 0;
	n = va_arg(*args, unsigned int);
	ft_put_num_base(n, "0123456789", 10);
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
