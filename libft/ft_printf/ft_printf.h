/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:25:04 by mfornovi          #+#    #+#             */
/*   Updated: 2024/10/07 10:25:08 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_puthex(unsigned long long n, int c);
int	ft_putptr(void *ptr);
int	ft_putchar(int c);
int	ft_putnbr(int n);
int	ft_putstr(char *s);
int	ft_printf(const char *input, ...);
int	ft_puthex(unsigned long long num, int cap);
int	ft_putptr(void *ptr);
int	ft_putnbr_unsigned(unsigned int n);
#endif
