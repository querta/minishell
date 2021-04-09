/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 03:16:56 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 12:55:41 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n)
{
	size_t			i;
	unsigned char	*ret;

	i = 0;
	while (i < n && ((unsigned char *)src)[i] != (unsigned char)c)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	if (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		ret = &((unsigned char *)dst)[i + 1];
		return ((void *)ret);
	}
	return (0);
}
