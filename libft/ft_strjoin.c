/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:33:47 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/23 17:18:55 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	n1;
	size_t	n2;

	new = malloc (((ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1)
			* sizeof(char));
	if (!new)
		return (NULL);
	n1 = 0;
	n2 = 0;
	while (s1[n1])
	{
		new[n1] = s1[n1];
		n1++;
	}
	while (s2[n2])
	{
		new[n1] = s2[n2];
		n1++;
		n2++;
	}
	new[n1] = '\0';
	return (new);
}
/*
#include <stdio.h>
int main(void)
{
	char *result;
	result = ft_strjoin("", "");
	printf("%s", result);
}
*/
