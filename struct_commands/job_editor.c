/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:02:10 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:01:15 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*ft_job_creater(t_main *mn, char *str)
{
	t_job	*job;

	job = NULL;
	if (!(job = malloc(sizeof(t_job))))
		return (ft_null_error(3, mn, NULL));
	job->act_pip = NULL;
	if (!(job->pipe = ft_pipe_creater(mn, str)))
	{
		free(job);
		return (NULL);
	}
	job->act_pip = job->pipe;
	return (job);
}

int		ft_job_clear(t_job **lst, int sig)
{
	t_pipe	*pip;

	pip = NULL;
	while ((*(lst))->pipe)
	{
		pip = (*(lst))->pipe->next;
		ft_rdir_clear(&((*(lst))->pipe->redir), 0);
		free((*(lst))->pipe);
		(*(lst))->pipe = pip;
	}
	free((*(lst)));
	(*(lst)) = NULL;
	if (sig == 0)
		return (-1);
	return (1);
}
