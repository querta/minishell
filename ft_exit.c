/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:21:46 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 17:21:52 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		errno_cmd(t_main *mn)
{
	t_rdir *rdir;

	rdir = mn->job->pipe->redir;
	write(2, mn->name_shell, ft_strlen(mn->name_shell) - 2);
	write(2, ": ", 2);
	ft_putstr_fd(mn->job->pipe->redir->sc, 2);
	write(2, ": ", 2);
	if (ft_strlen(rdir->sc) == 2 && ft_strncmp(rdir->sc, "cd", 2) == 0)
	{
		ft_putstr_fd(mn->job->pipe->redir->arg[0], 2);
		write(2, ": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
	mn->err = 1;
}

void		error_cmd(t_main *mn, t_rdir *rdir, int dir)
{
	write(2, mn->name_shell, ft_strlen(mn->name_shell) - 2);
	write(2, ": ", 2);
	ft_putstr_fd(rdir->sc, 2);
	write(2, ": ", 2);
	if (dir)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd("command not found", 2);
	mn->err = 127;
	exit(127);
}

static int	exit_free(t_main *mn)
{
	int		i;
	t_list	*lex;

	i = 0;
	ft_save_history(mn);
	while (mn->lexer)
	{
		lex = mn->lexer->next;
		free(mn->lexer->content);
		free(mn->lexer);
		mn->lexer = lex;
	}
	free(mn->name_shell);
	while (mn->envp[i])
		free(mn->envp[i++]);
	free(mn->envp);
	free(mn);
	exit(mn->err);
}

static int	run_exit(t_main *mn, t_rdir *rdir)
{
	if (!rdir->arg)
		return (1);
	else if (!ft_strisdigit(rdir->arg[0]))
	{
		write(1, mn->name_shell, ft_strlen(mn->name_shell) - 2);
		ft_putendl_fd(": exit: numeric argument required", 1);
		mn->err = 255;
	}
	else if (!rdir->arg[1])
		mn->err = ft_atoi(rdir->arg[0]);
	else
	{
		write(1, mn->name_shell, ft_strlen(mn->name_shell) - 2);
		ft_putendl_fd(": exit: too many arguments", 1);
		mn->err = 1;
		return (0);
	}
	return (1);
}

void		ft_exit(t_main *mn, t_pipe *piptmp, int status)
{
	t_rdir	*rdir;

	if (piptmp)
		rdir = piptmp->redir;
	if (status == SUCCESS)
	{
		ft_save_history(mn);
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (status == EXIT)
	{
		if (mn->job->pipe == piptmp)
			ft_putendl_fd("exit", 1);
		if (run_exit(mn, rdir) && mn->job->pipe == piptmp)
			exit_free(mn);
	}
	else if (status == MALLOC)
	{
		ft_putendl_fd("memory error", 1);
		exit_free(mn);
	}
}
