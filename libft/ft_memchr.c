/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:34:02 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 12:38:30 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ret_val;

	i = 0;
	ret_val = 0;
	while (i < n)
	{
		if (((unsigned char*)s)[i] == (unsigned char)c)
		{
			ret_val = &((unsigned char*)s)[i];
			break ;
		}
		i++;
	}
	return (ret_val);
}
