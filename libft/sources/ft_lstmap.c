/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:32:26 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/05 19:24:17 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *fresh;
	t_list *res;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	res = NULL;
	while (lst != NULL)
	{
		if (!(fresh = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, fresh);
		lst = lst->next;
	}
	return (res);
}
