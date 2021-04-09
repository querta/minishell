/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:49 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 14:59:37 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src,
					size_t dstsize)
{
	size_t	i;
	size_t	j;

	if ((dst != 0 || src != 0))
	{
		j = 0;
		i = ft_strlen(dst);
		if (i > dstsize)
			i = dstsize;
		while ((i + j + 1) < dstsize && src[j] != 0)
		{
			dst[i + j] = src[j];
			j++;
		}
		if (i < dstsize)
			dst[i + j] = '\0';
		return (i + ft_strlen(src));
	}
	return (0);
}
