/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:27:31 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/06 19:19:44 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_env(t_main *mn, int export)
{
	int	i;

	i = 0;
	if (!export)
	{
		while (mn->envp[i])
		{
			dup2(1, 0);
			if (ft_strchr(mn->envp[i], '='))
				ft_putendl_fd(mn->envp[i], 1);
			i++;
		}
	}
	if (export)
		print_export(mn->envp);
}

static int	search_var(t_main *mn, char *arg, int qi, char *fl)
{
	char	*eq;
	int		i;
	int		len;

	i = 0;
	while (mn->envp[i])
	{
		eq = ft_strchr(mn->envp[i], '=');
		if (!eq)
			eq = ft_strchr(mn->envp[i], '\0');
		len = eq - mn->envp[i];
		if (len == qi && !ft_strncmp(mn->envp[i], arg, len))
		{
			if (!*fl)
				return (1);
			free(mn->envp[i]);
			mn->envp[i] = ft_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void		check_var_export(t_main *mn, char *arg)
{
	char	*eq;
	int		i;

	eq = ft_strchr(arg, '=');
	if (!eq)
		eq = ft_strchr(arg, '\0');
	i = eq - arg;
	if (!search_var(mn, arg, i, eq))
		addnew_env(mn, arg);
}

int			run_export(t_main *mn, t_pipe *piptmp)
{
	t_rdir	*rdir;
	int		i;

	rdir = piptmp->redir;
	if (ft_strncmp(rdir->sc, "export=", 7) == 0)
		return (1);
	else if (!rdir->into_arg)
		run_env(mn, 1);
	else if (rdir == mn->job->pipe->redir)
	{
		i = 0;
		while (i < rdir->into_arg)
		{
			if (validate_var_str(rdir->arg[i], 1))
				check_var_export(mn, rdir->arg[i]);
			else
				error_var(mn, "export", rdir->arg[i]);
			i++;
		}
	}
	return (1);
}
