/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:26:22 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/28 10:33:46 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*box;

	box = (*lst);
	if (lst)
	{
		while (*lst)
		{
			box = (*lst)-> next;
			ft_lstdelone(*lst, del);
			(*lst) = box;
		}
	}
}
