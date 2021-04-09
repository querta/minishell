/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:56:28 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/06 16:20:50 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_error(t_main *mn, char *str)
{
	write(2, mn->name_shell, ft_strlen(mn->name_shell) - 2);
	write(2, ": ", 2);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	mn->err = 1;
	return (-1);
}

int			check_redir(t_main *mn, t_pipe *piptmp)
{
	t_rdir *rdir;

	rdir = piptmp->redir;
	if (!rdir->dir)
		return (0);
	while (rdir)
	{
		if (rdir->next)
		{
			if (rdir->dir == 1)
				mn->rfd[0] = open(rdir->next->sc, O_RDONLY);
			if (rdir->dir == 2 || rdir->dir == 3)
				close(mn->rfd[1]);
			if (rdir->dir == 2)
				mn->rfd[1] = open(rdir->next->sc,
					O_CREAT | O_WRONLY | O_TRUNC, 416);
			if (rdir->dir == 3)
				mn->rfd[1] = open(rdir->next->sc,
					O_CREAT | O_WRONLY | O_APPEND, 416);
			if (mn->rfd[1] == -1 || mn->rfd[0] == -1)
				return (open_error(mn, rdir->next->sc));
		}
		rdir = rdir->next;
	}
	return (1);
}

static void	create_forks(t_main *mn, t_pipe *piptmp)
{
	pid_t pid;

	pid = fork();
	if (!pid)
	{
		dup2(mn->rfd[1], 1);
		dup2(mn->rfd[0], 0);
		if (!buildin_funcs(mn, piptmp))
			external_funcs(mn, piptmp);
		close(mn->rfd[1]);
		dup2(mn->rfd[1], 1);
		exit(mn->err);
	}
	else
	{
		dup2(mn->rfd[1], 0);
		waitpid(pid, &mn->err, 0);
		mn->err = WEXITSTATUS(mn->err);
		close(mn->rfd[1]);
		dup2(mn->temp0fd, 0);
	}
}

void		exec_redirs(t_main *mn, t_pipe *piptmp)
{
	int		red;

	mn->rfd[0] = dup(0);
	if ((red = check_redir(mn, piptmp)) < 0)
		dup2(mn->temp0fd, 0);
	else if (red > 0)
		create_forks(mn, piptmp);
	else if (red == 0)
	{
		if (!buildin_funcs(mn, piptmp))
			external_funcs(mn, piptmp);
		dup2(mn->temp0fd, 0);
	}
}
