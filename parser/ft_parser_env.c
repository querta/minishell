/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:11:31 by spitt             #+#    #+#             */
/*   Updated: 2021/04/06 12:44:33 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	p_to_po_array_joiner(char *str, t_job **new_job)
{
	char	**tmp;
	int		i;

	i = 0;
	(*(new_job))->act_pip->act_rd->into_arg += 1;
	tmp = (*(new_job))->act_pip->act_rd->arg;
	if (!((*(new_job))->act_pip->act_rd->arg = malloc(sizeof(char *) *
			(*(new_job))->act_pip->act_rd->into_arg)))
		return (ft_errors(0));
	while (i < (*(new_job))->act_pip->act_rd->into_arg - 1)
	{
		if (!((*(new_job))->act_pip->act_rd->arg[i] = ft_strdup(tmp[i])))
			return (ft_errors(0));
		i++;
	}
	if (!((*(new_job))->act_pip->act_rd->arg[i++] = ft_strdup(str)))
		return (ft_errors(0));
	i = 0;
	while (i < (*(new_job))->act_pip->act_rd->into_arg - 1)
		free(tmp[i++]);
	free(tmp);
	return (1);
}

static int	p_to_po_array_creater(char *str, t_job **new_job)
{
	char	**tmp;

	tmp = NULL;
	if (!((*(new_job))->act_pip->act_rd->arg = malloc(sizeof(char *))))
		return (-1);
	tmp = (*(new_job))->act_pip->act_rd->arg;
	(*(new_job))->act_pip->act_rd->into_arg = 1;
	if (!(*tmp = ft_strdup(str)))
		return (ft_errors(0));
	return (1);
}

static int	redirect_cont(t_main *mn, char *tmp, char *str, t_job **new_job)
{
	mn->current_lexer = mn->current_lexer->next;
	if (mn->current_lexer->next)
		tmp = mn->current_lexer->next->content;
	else
		return (ft_errors(1));
	if ((*tmp == 60 || *tmp == 62))
		return (ft_errors(1));
	if (*str == 62)
		(*(new_job))->act_pip->act_rd->dir = 3;
	else
		(*(new_job))->act_pip->act_rd->dir = 1;
	return (1);
}

static int	redirect_dirs(t_main *mn, char *str, t_rdir *new_dir,
							t_job **new_job)
{
	char	*tmp;

	tmp = NULL;
	if (mn->current_lexer->next)
		tmp = mn->current_lexer->next->content;
	if ((*str == 62 && tmp && *tmp == 62) || (*str == 60 && tmp && *tmp == 60))
	{
		if ((redirect_cont(mn, tmp, str, new_job)) < 0)
			return (-1);
	}
	else if (*str == 62 && tmp && *tmp != 62 && tmp && *tmp != 60)
		(*(new_job))->act_pip->act_rd->dir = 2;
	else if (*str == 60 && tmp && *tmp != 62 && tmp && *tmp != 60)
		(*(new_job))->act_pip->act_rd->dir = 1;
	else
		return (ft_errors(1));
	mn->current_lexer = mn->current_lexer->next;
	str = mn->current_lexer->content;
	if (!(new_dir = ft_rdir_creater(mn, str)))
		return (-1);
	(*(new_job))->act_pip->act_rd->next = new_dir;
	(*(new_job))->act_pip->act_rd = new_dir;
	return (1);
}

int			redirect_searcher(t_main *mn, char *str, t_job **new_job)
{
	t_rdir	*new_dir;

	new_dir = NULL;
	if (*str == 62 || *str == 60)
		return (redirect_dirs(mn, str, new_dir, new_job));
	else
	{
		if ((*(new_job))->act_pip->act_rd->into_arg == 0)
			return (p_to_po_array_creater(str, new_job));
		else
			return (p_to_po_array_joiner(str, new_job));
	}
}
