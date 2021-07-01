/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:01:29 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:01:21 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*ft_pipe_creater(t_main *mn, char *str)
{
	t_pipe	*pipe;

	pipe = NULL;
	if (!(pipe = malloc(sizeof(t_pipe))))
		return (ft_null_error(3, mn, NULL));
	pipe->redir = NULL;
	if (!(pipe->redir = ft_rdir_creater(mn, str)))
	{
		free(pipe);
		return (NULL);
	}
	pipe->act_rd = pipe->redir;
	pipe->next = NULL;
	return (pipe);
}

void	ft_pipe_clear(t_pipe **lst)
{
	t_pipe	*next_remove_element;
	int		i;

	while ((*lst))
	{
		i = 0;
		next_remove_element = (*(lst))->next;
		if ((*(lst))->redir)
			ft_rdir_clear(&(*(lst))->redir, 0);
		free(*(lst));
		(*(lst)) = next_remove_element;
	}
	free((*lst));
}

t_pipe	*ft_pipelast(t_pipe *lst)
{
	t_pipe	*ret_struct;

	if (!lst)
		return (lst);
	while (lst)
	{
		ret_struct = lst;
		lst = lst->next;
	}
	return (ret_struct);
}

void	ft_pipe_addback(t_pipe **lst, t_pipe *ft_new)
{
	t_pipe	*last_element;

	if (!*(lst))
		*(lst) = ft_new;
	else
	{
		last_element = ft_pipelast(*(lst));
		last_element->next = ft_new;
	}
}
