/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:13:43 by mfornovi          #+#    #+#             */
/*   Updated: 2024/10/07 11:13:45 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	c;
	int	len;

	len = 0;
	c = 0;
	if (str)
	{
		while (str[c] != '\0')
		{
			len += ft_putchar(str[c]);
			c++;
		}
	}
	else
	{
		ft_putstr("(null)");
		return (6);
	}
	return (len);
}
/*
int	main(void)
{
	ft_putstr("hello");
}
*/
