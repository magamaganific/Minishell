/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:16:25 by mfornovi          #+#    #+#             */
/*   Updated: 2024/09/28 10:34:22 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*nobj;

	if (!lst || !f || !del)
		return (NULL);
	nlst = NULL;
	while (lst)
	{
		nobj = ft_lstnew(lst -> content);
		if (!nobj)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		nobj -> content = (f(nobj -> content));
		ft_lstadd_back(&nlst, nobj);
		lst = lst -> next;
	}
	return (nlst);
}
