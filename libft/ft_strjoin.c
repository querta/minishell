/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:49:48 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 15:58:27 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_cpy(char *str, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;

	if (s1 != 0 && s2 != 0)
	{
		new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (new_str == 0)
			return (0);
		str_cpy(new_str, s1, s2);
		return (new_str);
	}
	return (0);
}
