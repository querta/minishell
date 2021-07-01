/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:08:31 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 20:17:17 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_remove_element;

	while ((*lst))
	{
		next_remove_element = (*(lst))->next;
		(*del)((*(lst))->content);
		free(*(lst));
		(*(lst)) = next_remove_element;
	}
	free((*lst));
}
