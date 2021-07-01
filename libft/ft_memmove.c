/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:11:16 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 10:56:52 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (dst != src)
	{
		if (dst > src)
		{
			while (len > i)
			{
				((unsigned char *)dst)[len - 1] =
				((unsigned char *)src)[len - 1];
				len--;
			}
		}
		else
			dst = ft_memcpy(dst, src, len);
	}
	return (dst);
}
