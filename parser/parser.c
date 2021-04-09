/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:01:12 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 21:21:00 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pars_cont(t_main *mn, t_job **new_job, t_list *lst)
{
	t_list	*lst_2;

	lst_2 = NULL;
	mn->job = (*(new_job));
	executer(mn);
	ft_job_clear(new_job, 1);
	mn->current_lexer = lst;
	while (mn->current_lexer)
	{
		lst_2 = mn->current_lexer->next;
		if (((char*)mn->current_lexer->content)[0] != 0)
			free(mn->current_lexer->content);
		free(mn->current_lexer);
		mn->current_lexer = NULL;
		mn->current_lexer = lst_2;
	}
}

static int	pipes_searcher(t_main *mn, char *str, t_job **new_job)
{
	t_pipe	*new_pipe;

	new_pipe = NULL;
	if (*str == 124)
	{
		mn->current_lexer = mn->current_lexer->next;
		if (mn->current_lexer)
			str = mn->current_lexer->content;
		if (!(new_pipe = ft_pipe_creater(mn, str)))
			return (ft_errors(3));
		ft_pipe_addback(&((*(new_job))->pipe), new_pipe);
		(*(new_job))->act_pip = new_pipe;
		return (1);
	}
	if ((redirect_searcher(mn, str, new_job)) < 0)
		return (-1);
	return (1);
}

static int	semicolon_searcher(t_main *mn, t_job **new_job)
{
	char	*str;

	str = mn->current_lexer->content;
	if (!(*(new_job)))
	{
		if (!((*(new_job)) = ft_job_creater(mn, str)))
			return (-1);
		return (0);
	}
	if ((pipes_searcher(mn, str, new_job)) < 0)
		return (ft_job_clear(new_job, 0));
	return (0);
}

int			parser_shell(t_main *mn)
{
	t_job	*new_job;
	t_list	*lst;

	new_job = NULL;
	lst = NULL;
	if (!mn->lexer)
		return (1);
	while (mn->lexer)
	{
		lst = ft_string_rewriter(mn);
		mn->current_lexer = lst;
		while (mn->current_lexer)
		{
			mn->car = semicolon_searcher(mn, &new_job);
			if (mn->car == 1 && mn->current_lexer->next != NULL)
				break ;
			if (mn->car == -1)
				return (-1);
			mn->current_lexer = mn->current_lexer->next;
		}
		ft_pars_cont(mn, &new_job, lst);
	}
	mn->lexer = NULL;
	return (1);
}
