/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:33:47 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 11:11:13 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	copy_str(char *restrict dst, const char *restrict src,
							size_t dstsize)
{
	size_t i;

	i = 0;
	while (i < dstsize && ((unsigned char *)src)[i] != 0)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	((unsigned char *)dst)[i] = 0;
	return (i);
}

size_t			ft_strlcpy(char *restrict dst, const char *restrict src,
							size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	else
	{
		dstsize -= 1;
		if ((i = copy_str(dst, src, dstsize)) < dstsize)
			return (i);
		else
			return (ft_strlen(src));
	}
}
