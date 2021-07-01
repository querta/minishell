/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:30:52 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:29:29 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	rec_set(char const *str, char const *set,
					unsigned long s_ind, unsigned long ret_val)
{
	unsigned long	j;

	j = 0;
	while (set[j] != 0)
	{
		if (str[s_ind + ret_val] == set[j])
			break ;
		j++;
	}
	return (j);
}

static int	end_str(char const *str, char const *set, unsigned long s_ind)
{
	unsigned long	ret_val;
	unsigned long	j;
	unsigned long	pr;

	ret_val = 0;
	j = 0;
	pr = 0;
	while (str[s_ind] != 0)
	{
		while (str[s_ind + ret_val] != 0)
		{
			j = rec_set(str, set, s_ind, ret_val);
			if (set[j] == 0)
				pr++;
			ret_val++;
			j = 0;
		}
		if (pr == 0)
			break ;
		pr = 0;
		s_ind++;
		ret_val = 1;
	}
	return (s_ind);
}

static int	start_str(char const *str, char const *set)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		while (set[j] != 0)
		{
			if (str[i] == set[j])
				break ;
			j++;
		}
		if (set[j] == 0)
			break ;
		i++;
		j = 0;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	k;
	char			*new_str;

	i = 0;
	j = 0;
	k = 0;
	if (!s1)
		return (NULL);
	i = start_str(s1, set);
	j = end_str(s1, set, i);
	new_str = malloc(j - i + 2);
	if (new_str != 0)
	{
		while (k <= (j - i))
		{
			new_str[k] = s1[i + k];
			k++;
		}
		new_str[k] = '\0';
		return (new_str);
	}
	return (NULL);
}
