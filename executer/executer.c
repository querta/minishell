/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:15:40 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 21:39:45 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(t_main *mn, t_pipe *piptmp)
{
	if (piptmp->next)
	{
		mn->n_count = 0;
		mn->fd[0] = 0;
		mn->fd[1] = 0;
		pipe(mn->fd);
		return (1);
	}
	else
		return (0);
}

static void	create_forks(t_main *mn, t_pipe *piptmp)
{
	pid_t pid;

	pid = fork();
	if (!pid)
	{
		mn->pid = 0;
		dup2(mn->fd[1], 1);
		close(mn->fd[0]);
		exec_redirs(mn, piptmp);
		close(mn->fd[1]);
		exit(mn->err);
	}
	else
	{
		dup2(mn->fd[0], 0);
		close(mn->fd[1]);
		wait(&pid);
		mn->pid = 1;
		close(mn->fd[0]);
	}
}

int			executer(t_main *mn)
{
	t_pipe *piptmp;

	piptmp = mn->job->pipe;
	mn->temp0fd = dup(0);
	while (piptmp)
	{
		if (check_pipe(mn, piptmp))
			create_forks(mn, piptmp);
		else
		{
			exec_redirs(mn, piptmp);
			dup2(mn->temp0fd, 0);
		}
		piptmp = piptmp->next;
	}
	dup2(mn->temp0fd, 0);
	return (1);
}
