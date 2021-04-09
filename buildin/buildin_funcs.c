/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:24:36 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 20:44:57 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			validate_var_str(char *arg, int eq)
{
	int i;

	i = -1;
	if (ft_isdigit(arg[0]))
		return (0);
	if (eq)
	{
		if (arg[0] == '=')
			return (0);
		while (arg[++i] && arg[i] != '=')
		{
			if (!ft_symbols(arg[i]))
				return (0);
		}
	}
	else if (!eq)
	{
		while (arg[++i])
		{
			if (!ft_symbols(arg[i]))
				return (0);
		}
	}
	return (1);
}

static void	clear_file(t_main *mn)
{
	int		fd;
	t_rdir	*rdir;

	rdir = mn->job->pipe->redir;
	if (mn->job->pipe->redir->dir)
	{
		if (rdir->dir == 2)
		{
			fd = open(rdir->arg[0], O_CREAT | O_RDWR | O_TRUNC, 416);
			close(fd);
		}
	}
}

static int	check_exunset(t_rdir *rdir, int exp)
{
	if (exp)
	{
		if (ft_strlen(rdir->sc) == 6 && ft_strncmp(rdir->sc, "export", 6) == 0)
			return (1);
		else if (ft_strncmp(rdir->sc, "export=", 7) == 0)
			return (1);
	}
	else if (!exp)
	{
		if (ft_strlen(rdir->sc) == 5 && ft_strncmp(rdir->sc, "unset", 5) == 0)
			return (1);
		else if (ft_strncmp(rdir->sc, "unset=", 6) == 0)
			return (1);
	}
	return (0);
}

int			buildin_funcs(t_main *mn, t_pipe *piptmp)
{
	char	path[PATH_MAX];
	t_rdir	*rdir;

	rdir = piptmp->redir;
	if (ft_strlen(rdir->sc) == 3 && ft_strncmp(rdir->sc, "env", 3) == 0)
		run_env(mn, 0);
	else if (ft_strlen(rdir->sc) == 4 && ft_strncmp(rdir->sc, "exit", 4) == 0)
		ft_exit(mn, piptmp, EXIT);
	else if (ft_strlen(rdir->sc) == 3 && ft_strncmp(rdir->sc, "pwd", 3) == 0)
		ft_putendl_fd(getwd(path), 1);
	else if (ft_strlen(rdir->sc) == 4 && ft_strncmp(rdir->sc, "echo", 4) == 0)
		run_echo(mn, piptmp);
	else if (check_exunset(rdir, 1))
		return (run_export(mn, piptmp));
	else if (check_exunset(rdir, 0))
		run_unset(mn, piptmp);
	else if (ft_strlen(rdir->sc) == 2 && ft_strncmp(rdir->sc, "cd", 2) == 0)
		return (run_cd(mn, rdir));
	else if (ft_strlen(rdir->sc) == 0 && ft_strncmp(rdir->sc, "", 1) == 0)
		clear_file(mn);
	else
		return (0);
	mn->err = 0;
	return (1);
}
