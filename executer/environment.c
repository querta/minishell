/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:35:18 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/06 15:07:36 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addnew_env(t_main *mn, char *arg)
{
	char	**tmparr;

	tmparr = addtoarr(mn->envp, arg);
	free(mn->envp);
	mn->envp = tmparr;
}

int		search_env_index(t_main *mn, char *var)
{
	int		i;
	char	*eq;
	int		len;

	i = 0;
	while (mn->envp[i])
	{
		eq = ft_strchr(mn->envp[i], '=');
		if (!eq)
			eq = ft_strchr(mn->envp[i], '\0');
		len = eq - mn->envp[i];
		if (len == (int)ft_strlen(var) &&
			!ft_strncmp(mn->envp[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

char	*search_env(t_main *mn, char *var)
{
	int		i;
	char	*eq;
	int		len;

	i = 0;
	while (mn->envp[i])
	{
		eq = ft_strchr(mn->envp[i], '=');
		if (!eq)
			eq = ft_strchr(mn->envp[i], '\0');
		len = eq - mn->envp[i];
		if (len == (int)ft_strlen(var) &&
			!ft_strncmp(mn->envp[i], var, ft_strlen(var)))
			return (&(mn->envp[i][len + 1]));
		i++;
	}
	return (0);
}

void	print_export(char **arr)
{
	int	i;
	int	k;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		k = 0;
		while (arr[i][k])
		{
			write(1, &(arr[i][k]), 1);
			if (arr[i][k] == '=')
				write(1, "\"", 1);
			k++;
		}
		if (arr[i][k] == '\0' && ft_strchr(arr[i], '='))
			write(1, "\"", 1);
		ft_putendl_fd("", 1);
		i++;
	}
}
