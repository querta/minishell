/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:27:55 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 17:23:10 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int		ft_symbols(char s)
{
	if (ft_isalnum(s) || s == '#' || s == '$' || s == '_')
		return (1);
	return (0);
}

int		count_all_args(t_pipe *piptmp)
{
	t_rdir	*rdir;
	int		count;

	count = 0;
	rdir = piptmp->redir;
	while (rdir)
	{
		count += rdir->into_arg;
		rdir = rdir->next;
	}
	return (count);
}

char	**addtoarr(char **arr, char *str)
{
	int		i;
	char	**newarr;

	i = 0;
	while (arr[i])
		i++;
	if (str)
		i++;
	if (!(newarr = (char **)ft_calloc(i + 1, sizeof(char *))))
		return (0);
	i = 0;
	while (arr[i])
	{
		newarr[i] = ft_strdup(arr[i]);
		i++;
	}
	if (str)
	{
		newarr[i] = ft_strdup(str);
		i++;
	}
	newarr[i] = 0;
	return (newarr);
}

int		ft_isspace(char c)
{
	if (!c)
		return (0);
	if (c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
