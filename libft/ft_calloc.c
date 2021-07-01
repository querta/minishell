/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:35:55 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 15:10:09 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret_val;
	size_t			i;

	i = 0;
	ret_val = malloc(count * size);
	if (ret_val)
	{
		while (i < (count * size))
		{
			ret_val[i] = 0;
			i++;
		}
		return (ret_val);
	}
	return (NULL);
}
