/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:03:50 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/26 13:04:44 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned int	n;
	char			*res;

	res = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!res)
		return (NULL);
	n = 0;
	while (n < ft_strlen(s))
	{
		res[n] = (*f)(n, s[n]);
		n++;
	}
	res[n] = 0;
	return (res);
}
