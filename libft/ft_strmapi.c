/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:58:25 by spitt             #+#    #+#             */
/*   Updated: 2020/11/05 19:19:32 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*ret_str;

	i = 0;
	j = 0;
	if (s == 0)
		return (0);
	while (s[i] != 0)
		i++;
	ret_str = malloc(i + 1);
	if (ret_str != 0)
	{
		while (j < i)
		{
			ret_str[j] = (*f)(j, s[j]);
			j++;
		}
		ret_str[j] = '\0';
		return (ret_str);
	}
	return (0);
}
