/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:01:41 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:03:06 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdir	*ft_dir_creater_cont(t_main *mn, char *str, t_rdir *rdir, char *lex)
{
	if (!(rdir->sc = ft_strdup("")))
		return (ft_null_error(3, mn, rdir));
	if (*str == 60)
		rdir->dir = 1;
	if (*str == 62 && *lex != 62)
		rdir->dir = 2;
	if (*str == 62 && *lex == 62)
	{
		rdir->dir = 3;
		mn->current_lexer = mn->current_lexer->next;
	}
	return (rdir);
}

t_rdir	*ft_dir_creater(t_main *mn, char *str, t_rdir *rdir)
{
	char	*lex;
	char	*lex_next;

	lex = NULL;
	lex_next = NULL;
	if (mn->current_lexer->next)
	{
		lex = mn->current_lexer->next->content;
		if (mn->current_lexer->next->next)
			lex_next = mn->current_lexer->next->next->content;
	}
	if (!(rdir = ft_dir_creater_cont(mn, str, rdir, lex)))
		return (NULL);
	return (rdir);
}

t_rdir	*ft_rdir_creater(t_main *mn, char *str)
{
	t_rdir	*rdir;

	rdir = NULL;
	if (!(rdir = ft_calloc(sizeof(t_rdir), 1)))
		return (ft_null_error(3, mn, NULL));
	if ((*str == 60 || *str == 62))
		return (ft_dir_creater(mn, str, rdir));
	if (!(rdir->sc = ft_strdup(str)))
		return (ft_null_error(3, mn, rdir));
	return (rdir);
}

void	ft_rdir_addback(t_rdir **lst, t_rdir *ft_new, t_main *mn)
{
	t_rdir	*last_element;

	if (!*(lst))
		*(lst) = ft_new;
	else
	{
		last_element = *(lst);
		while (last_element->next)
			last_element = last_element->next;
		last_element->next = ft_new;
		mn->job->act_pip->act_rd = ft_new;
	}
}

void	ft_rdir_clear(t_rdir **lst, int i)
{
	t_rdir	*next_remove_element;

	while ((*lst))
	{
		next_remove_element = (*(lst))->next;
		if ((*(lst))->sc)
			free((*(lst))->sc);
		if ((*(lst))->into_arg > 0)
		{
			while (i < (*(lst))->into_arg)
				free((*(lst))->arg[i++]);
			free((*(lst))->arg);
		}
		i = 0;
		if ((*(lst))->into_com > 0)
		{
			while (i < (*(lst))->into_com)
				free((*(lst))->com[i++]);
			free((*(lst))->com);
		}
		free(*(lst));
		(*(lst)) = NULL;
		(*(lst)) = next_remove_element;
	}
	free((*lst));
}
