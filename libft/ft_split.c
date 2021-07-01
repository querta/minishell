/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:43:36 by spitt             #+#    #+#             */
/*   Updated: 2021/03/10 20:37:24 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_arr(char const *s, char c, size_t *arr_mod)
{
	size_t	i;

	i = 1;
	arr_mod[0] = ft_strlen(s);
	arr_mod[1] = 0;
	arr_mod[4] = 0;
	arr_mod[5] = 0;
	while (i < arr_mod[0])
	{
		if (s[i] == c && s[i - 1] != c)
			arr_mod[1] += 1;
		i++;
	}
	if (s[i - 1] != c)
		arr_mod[1] += 1;
	return (arr_mod[1]);
}

static void		per_str(char *str, char const *s, size_t *arr_mod, size_t mod)
{
	size_t	i;
	size_t	j;

	if (mod == 0)
	{
		i = arr_mod[2];
		j = 0;
		while (i < (arr_mod[4] - 1))
		{
			str[j] = s[i];
			i++;
			j++;
		}
		str[j] = '\0';
	}
	if (mod == 1)
	{
		j = 0;
		i = ft_strlen(s) - ft_strlen(str);
		arr_mod[2] = i;
		arr_mod[3] += 1;
	}
}

static char		*new_str(char const *s, char c, size_t *arr_mod)
{
	size_t	i;
	char	*str;

	arr_mod[2] = arr_mod[4];
	i = arr_mod[2];
	arr_mod[3] = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && arr_mod[3] == 0)
			per_str(&((char *)s)[i], s, arr_mod, 1);
		else if (s[i] == c && arr_mod[3] != 0)
		{
			arr_mod[3] += 1;
			break ;
		}
		else if (s[i] != c && arr_mod[3] != 0)
			arr_mod[3] += 1;
		i++;
	}
	if (s[i] == 0 && s[i - 1] != c)
		arr_mod[3] += 1;
	arr_mod[4] = i + 1;
	str = ft_substr((char *)s, arr_mod[2], (arr_mod[4] - arr_mod[2] - 1));
	return (str);
}

void			clean_memory(char **arr, size_t *arr_mod)
{
	size_t	i;

	i = 0;
	while (i <= arr_mod[1])
	{
		free(arr[i]);
		i++;
	}
}

char			**ft_split(char const *s, char c)
{
	size_t	arr_mod[6];
	char	**arr;

	if (s)
	{
		arr = malloc(sizeof(char *) * (size_arr(s, c, arr_mod) + 1));
		if (arr != 0)
		{
			while (arr_mod[5] < (arr_mod[1]))
			{
				arr[arr_mod[5]] = new_str(s, c, arr_mod);
				if (arr[arr_mod[5]] == 0)
				{
					clean_memory(arr, arr_mod);
					break ;
				}
				arr_mod[5] += 1;
			}
			arr[arr_mod[5]] = NULL;
			return (arr);
		}
	}
	return (0);
}
