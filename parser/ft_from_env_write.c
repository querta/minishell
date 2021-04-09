/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_from_env_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:39:12 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 12:13:17 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_from_env_write_cont(t_main *mn, int i, int j, char *path)
{
	char	**envp;
	char	*chr;

	chr = NULL;
	envp = mn->envp;
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
		return ;
	chr++;
	mn->car += ft_strlcpy(&mn->str[mn->car], chr, ((int)ft_strlen(chr) + 1));
}

static int	ft_write_errno(t_main *mn, int len)
{
	char	*str;
	int		i;

	str = NULL;
	str = ft_itoa(mn->err);
	i = (int)ft_strlen(str);
	len += ft_strlcpy(&mn->str[len], str, i + 1);
	free(str);
	mn->err = 0;
	return (len);
}

static int	ft_from_env_write_c(t_main *mn, char *path, int len, int i)
{
	mn->car = len;
	ft_from_env_write_cont(mn, 0, 0, path);
	len = mn->car;
	mn->car = i;
	free(path);
	return (len);
}

static int	ft_bucks(t_main *mn, int len, int i)
{
	if (i == 0)
		return (len);
	mn->car--;
	len += ft_strlcpy(&mn->str[len], "$", 2);
	return (len);
}

int			ft_from_env_write(t_main *mn, int len, char *src)
{
	int		i[2];
	char	*path;

	i[1] = -1;
	i[0] = ++mn->car;
	if (src[mn->car] == '?')
		return (ft_write_errno(mn, len));
	ft_search_vol_bucks(i, src);
	if ((--i[0] - mn->car) >= 0 && (mn->str[i[0]] < 48 || mn->str[i[0]] > 57))
	{
		if (!(path = ft_calloc((i[0] - mn->car) + 2, 1)))
			return (ft_errors(0));
	}
	else
		return (ft_bucks(mn, len, (i[0] - mn->car)));
	if (!path)
		return (0);
	while (++i[1] < i[0])
	{
		if (ft_print_symbs(src[mn->car + i[1]]) != 0)
			path[i[1]] = src[mn->car + i[1]];
	}
	return (ft_from_env_write_c(mn, path, len, i[0]));
}
