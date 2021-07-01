/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:36:15 by spitt             #+#    #+#             */
/*   Updated: 2020/11/08 12:58:17 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_string(char *stack, char *need, unsigned long i)
{
	size_t	j;
	int		flag;

	j = 0;
	flag = 0;
	while (need[j] != 0)
	{
		if (stack[i] == need[j])
		{
			flag = 1;
			i++;
			j++;
		}
		else
		{
			flag = 0;
			break ;
		}
	}
	return (flag);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ret_val;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret_val = 0;
	while (needle[j] != 0)
		j++;
	if (j == 0 && (int)needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i < len)
	{
		if (haystack[i] == needle[0])
		{
			if (check_string((char *)haystack, (char *)needle, i) == 1 &&
							(len - i) >= j)
			{
				ret_val = &((char *)haystack)[i];
				break ;
			}
		}
		i++;
	}
	return (ret_val);
}
