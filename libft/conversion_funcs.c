/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:23:37 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/16 12:23:41 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_char(va_list *args)
{
	char	c;

	c = (char)va_arg(*args, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_convert_str(va_list *args)
{
	char	*str;

	str = va_arg(*args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_convert_int(va_list *args)
{
	int	n;
	int	count;

	count = 0;
	n = va_arg(*args, int);
	ft_putnbr_fd(n, 1);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
