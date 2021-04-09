/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:03:52 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 10:43:57 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_element;

	if (!(*(lst)))
		(*(lst)) = new;
	else
	{
		last_element = ft_lstlast(*(lst));
		last_element->next = new;
	}
}
