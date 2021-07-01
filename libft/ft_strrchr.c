/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:30:20 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:30:12 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret_val;
	int		i;

	i = 0;
	if (c)
	{
		ret_val = 0;
		while ((int)s[i] != 0)
		{
			if ((int)s[i] == c)
				ret_val = &((char *)s)[i];
			i++;
		}
	}
	else
	{
		while ((int)s[i] != 0)
			i++;
		ret_val = &((char *)s)[i];
	}
	return (ret_val);
}
