/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:02:01 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 20:16:28 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ret_struct;

	if (!lst)
		return (lst);
	while (lst)
	{
		ret_struct = lst;
		lst = lst->next;
	}
	return (ret_struct);
}
