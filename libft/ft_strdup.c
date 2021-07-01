/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:51:52 by spitt             #+#    #+#             */
/*   Updated: 2021/02/15 14:41:16 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret_val;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	ret_val = malloc(len + 1);
	if (!ret_val)
		return (NULL);
	while (i < len)
	{
		ret_val[i] = s1[i];
		i++;
	}
	ret_val[i] = 0;
	return (ret_val);
}
