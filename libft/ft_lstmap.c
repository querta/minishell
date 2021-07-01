/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:13:58 by spitt             #+#    #+#             */
/*   Updated: 2020/11/09 12:24:27 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s_list;
	t_list	*new_element;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_element = ft_lstnew((*f)(lst->content));
	if (!new_element)
		return (NULL);
	s_list = new_element;
	lst = lst->next;
	while (lst != NULL)
	{
		new_element = ft_lstnew((*f)(lst->content));
		if (!new_element)
		{
			ft_lstclear(&s_list, del);
			return (NULL);
		}
		ft_lstadd_back(&s_list, new_element);
		lst = lst->next;
	}
	return (s_list);
}
