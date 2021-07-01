/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:12:31 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 11:20:00 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		while (s[0] != 0)
		{
			if (s[0] == c)
				break ;
			s++;
		}
		if (s[0] != 0 && c != 0)
			return ((char *)s);
		if (s[0] == 0 && c == 0)
			return ((char *)s);
	}
	else
	{
		while (s[0])
			((char *)s)[0] = ((char *)s)[0];
	}
	return (0);
}
