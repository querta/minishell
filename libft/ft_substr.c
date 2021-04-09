/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:43:19 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:28:58 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	length(char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i] != 0 && i < len)
		i++;
	return (i);
}

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_str;

	i = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
		i = length(s, start, len);
	new_str = malloc(i + 1);
	if (new_str != NULL)
	{
		if (i > 0)
		{
			i = 0;
			while (i < len && s[start + i] != 0)
			{
				new_str[i] = s[start + i];
				i++;
			}
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}
