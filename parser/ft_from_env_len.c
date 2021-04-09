/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_from_env_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:36:46 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:05:07 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_errno(t_main *mn)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	str = ft_itoa(mn->err);
	i = (int)ft_strlen(str);
	free(str);
	return (i);
}

static int	ft_from_env_len_cont(t_main *mn, int i, int j, char *path)
{
	char	**envp;
	char	*chr;

	envp = mn->envp;
	chr = NULL;
	while (envp[i])
	{
		if ((chr = ft_strchr(envp[i], '=')))
		{
			*chr = 0;
			if ((ft_strlen(path) == ft_strlen(envp[i])) &&
				(ft_strncmp(path, envp[i], (int)ft_strlen(path)) == 0))
				j = 1;
			*chr = '=';
		}
		if (j == 1)
			break ;
		i++;
	}
	if (!envp[i])
		return (0);
	return ((int)ft_strlen(++chr) + 1);
}

static int	ft_from_env_len_c(t_main *mn, char *path, int *i)
{
	path[i[1]] = 0;
	mn->car = i[0];
	i[0] = ft_from_env_len_cont(mn, 0, 0, path);
	free(path);
	return (i[0]);
}

void		ft_search_vol_bucks(int *i, char *src)
{
	int	sig;

	sig = 0;
	while (src[i[0]] && ft_print_symbs(src[i[0]]) != 0)
	{
		if (sig == 0 && (src[i[0]] > 47 && src[i[0]] < 58))
		{
			i[0]++;
			return ;
		}
		else if (sig == 0 && (src[i[0]] < 48 && src[i[0]] > 57))
			sig = 1;
		i[0]++;
	}
}

int			ft_from_env_len(t_main *mn)
{
	int		i[2];
	char	*path;

	path = NULL;
	mn->car++;
	i[1] = -1;
	i[0] = mn->car;
	if (mn->str[mn->car] && mn->str[mn->car] == '?')
		return (ft_len_errno(mn));
	ft_search_vol_bucks(i, mn->str);
	if ((--i[0] - mn->car) >= 0 && (mn->str[i[0]] < 48 || mn->str[i[0]] > 57))
	{
		if (!(path = ft_calloc((i[0] - mn->car) + 2, 1)))
			return (ft_errors(0));
	}
	else
		return (1);
	while (++i[1] < i[0])
	{
		if (ft_print_symbs(mn->str[mn->car + i[1]]) != 0)
			path[i[1]] = mn->str[mn->car + i[1]];
	}
	return (ft_from_env_len_c(mn, path, i));
}
