/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:29:17 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:25:32 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	int				ret_val;

	i = 0;
	ret_val = 0;
	while (i < n && (s1 || s2))
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			ret_val = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
			break ;
		}
		i++;
	}
	return (ret_val);
}
