/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:29:10 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 17:51:54 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_main *mn, t_pipe *piptmp, t_rdir *rdir)
{
	int i;

	if (rdir != piptmp->redir)
		write(1, " ", 1);
	i = 0;
	if (rdir->arg)
	{
		while (!ft_strncmp(rdir->arg[i], "-n", 3))
			i++;
	}
	while (i < rdir->into_arg)
	{
		mn->n_count += ft_strlen(rdir->arg[i]);
		ft_putstr_fd(rdir->arg[i], 1);
		if (i < rdir->into_arg - 1)
			write(1, " ", 1);
		i++;
	}
	mn->n_count += i - 2;
}

void		run_echo(t_main *mn, t_pipe *piptmp)
{
	int		nl;
	t_rdir	*rdir;

	nl = 1;
	rdir = piptmp->redir;
	if (rdir->arg)
		nl = ft_strncmp(rdir->arg[0], "-n", 3);
	while (rdir)
	{
		print_echo(mn, piptmp, rdir);
		rdir = rdir->next;
	}
	if (nl)
	{
		mn->n_count = 0;
		write(1, "\n", 1);
	}
}
