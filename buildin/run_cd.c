/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:29:30 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 17:17:53 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		update_env(t_main *mn, char *key, char *val)
{
	int		i;
	char	*tmp;
	char	*tmpstr;

	i = search_env_index(mn, key);
	tmp = ft_strjoin("=", val);
	tmpstr = ft_strjoin(key, tmp);
	if (i == -1)
		addnew_env(mn, tmpstr);
	else
	{
		free(mn->envp[i]);
		mn->envp[i] = ft_strjoin(key, tmp);
	}
	free(tmp);
	free(tmpstr);
}

static void	printerr(t_main *mn, char *cmd)
{
	write(2, mn->name_shell, ft_strlen(mn->name_shell) - 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(" not set", 2);
	mn->err = 1;
}

char		*checknopath(t_main *mn, t_rdir *rdir)
{
	char	*path;

	path = NULL;
	if (!rdir->arg)
	{
		if (!search_env(mn, "HOME"))
			printerr(mn, "HOME");
		else
			path = ft_strdup(search_env(mn, "HOME"));
	}
	else
	{
		if (rdir->arg[0][0] == '-' && rdir->arg[0][1] == '\0')
		{
			if (!search_env(mn, "OLDPWD"))
				printerr(mn, "OLDPWD");
			else
				path = ft_strdup(search_env(mn, "OLDPWD"));
		}
	}
	return (path);
}

static char	*makepath(t_main *mn, t_rdir *rdir)
{
	char *path;

	if (!rdir->arg || (rdir->arg[0][0] == '-' && rdir->arg[0][1] == '\0'))
		path = checknopath(mn, rdir);
	else
		path = ft_strdup(rdir->arg[0]);
	return (path);
}

int			run_cd(t_main *mn, t_rdir *rdir)
{
	char pwd[PATH_MAX];
	char *oldpwd;
	char *path;

	if ((path = makepath(mn, rdir)) == NULL)
		return (1);
	if (!mn->job->pipe->next)
	{
		if (!search_env(mn, "PWD"))
			oldpwd = ft_strdup("");
		else
			oldpwd = ft_strdup(search_env(mn, "PWD"));
		if (chdir(path) != 0)
			errno_cmd(mn);
		else
			mn->err = 0;
		getwd(pwd);
		update_env(mn, "PWD", pwd);
		update_env(mn, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	free(path);
	return (1);
}
