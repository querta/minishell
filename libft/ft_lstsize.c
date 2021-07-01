/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:56:04 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 20:12:28 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int	list_size;

	list_size = 0;
	if (!lst)
		return (list_size);
	while (lst)
	{
		lst = lst->next;
		list_size++;
	}
	return (list_size);
}
