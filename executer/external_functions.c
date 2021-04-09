/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:15:19 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/06 20:22:36 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_args(t_pipe *piptmp)
{
	int		i;
	int		k;
	char	**args;
	t_rdir	*rdir;

	i = 0;
	k = 1;
	args = ft_calloc(count_all_args(piptmp) + 2, sizeof(char *));
	rdir = piptmp->redir;
	while (rdir)
	{
		i = 0;
		while (i < rdir->into_arg)
		{
			args[k] = rdir->arg[i];
			i++;
			k++;
		}
		rdir = rdir->next;
	}
	return (args);
}

static int	find_path(t_main *mn, char **args, char *cmd)
{
	int		exec;
	int		i;
	char	**paths;

	paths = ft_split(search_env(mn, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		args[0] = ft_strjoin(paths[i], cmd);
		exec = execve(args[0], args, mn->envp);
		i++;
	}
	return (0);
}

static int	find_valid_prog(t_main *mn, char **args, t_pipe *piptmp)
{
	int		i;
	char	*cmd;

	i = 0;
	if (ft_strchr(piptmp->redir->sc, '/') || !search_env(mn, "PATH"))
	{
		cmd = ft_strdup(piptmp->redir->sc);
		args[0] = ft_strdup(cmd);
		if (execve(args[0], args, mn->envp) == -1)
		{
			free(cmd);
			error_cmd(mn, piptmp->redir, 1);
		}
	}
	else
	{
		cmd = ft_strjoin("/", piptmp->redir->sc);
		if (!find_path(mn, args, cmd))
		{
			free(cmd);
			return (-1);
		}
	}
	return (0);
}

static int	run_external(t_main *mn, t_pipe *piptmp)
{
	char	**args;

	args = fill_args(piptmp);
	if (find_valid_prog(mn, args, piptmp) == -1)
	{
		free(args[0]);
		free(args);
		return (-1);
	}
	free(args[0]);
	free(args);
	return (1);
}

int			external_funcs(t_main *mn, t_pipe *piptmp)
{
	pid_t	pid;

	pid = fork();
	mn->pid = 0;
	if ((ft_strlen(piptmp->redir->sc) == 4 &&
		(ft_strncmp(piptmp->redir->sc, "read", 4) == 0)))
		mn->pid = 1;
	if (!pid)
	{
		if (run_external(mn, piptmp) == -1)
			error_cmd(mn, piptmp->redir, 0);
	}
	else
	{
		waitpid(pid, &mn->err, 0);
		mn->err = WEXITSTATUS(mn->err);
	}
	mn->pid = 1;
	return (1);
}
