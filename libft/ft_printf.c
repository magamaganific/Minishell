/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:13:41 by elengarc          #+#    #+#             */
/*   Updated: 2025/04/16 11:13:43 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_and_convert(const char *str, va_list *args)
{
	if (str[1] == 'c')
		return (ft_convert_char(args));
	if (str[1] == 's')
		return (ft_convert_str(args));
	if (str[1] == 'p')
		return (ft_convert_hex_pointer(args));
	if (str[1] == 'd' || str[1] == 'i')
		return (ft_convert_int(args));
	if (str[1] == 'u')
		return (ft_convert_unsigned(args));
	if (str[1] == 'x')
		return (ft_convert_hex_min(args));
	if (str[1] == 'X')
		return (ft_convert_hex_max(args));
	if (str[1] == '%')
		return (ft_putchar_fd('%', 1), 1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			count = count + check_and_convert(format, &args);
			format = format + 2;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
			format++;
		}
	}
	va_end(args);
	return (count);
}
