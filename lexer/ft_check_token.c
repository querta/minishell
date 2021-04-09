/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:00:48 by spitt             #+#    #+#             */
/*   Updated: 2021/04/06 19:20:06 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_semicol_token(t_main *mn, t_list *lst, char *s, int *i)
{
	if ((i[0] == 0 || i[0] == 3) && !mn->lexer->next)
		return (ft_error_tocken(mn, 2, ";"));
	if (lst->next)
		s = lst->next->content;
	else
		s = NULL;
	if (s && *s == ';')
		return (ft_error_tocken(mn, 0, ";;"));
	i[0] = 2;
	return (1);
}

static int	ft_pipe_token(t_main *mn, t_list *lst, char *s, int *i)
{
	if (lst->next)
		s = lst->next->content;
	else
		s = NULL;
	if ((i[0] == 2 || i[0] == 0) && !s)
		return (ft_error_tocken(mn, 2, "|"));
	if (!s)
		return (ft_error_tocken(mn, 2, "newline"));
	if (s && *s == '|')
		return (ft_error_tocken(mn, 2, "|"));
	i[0] = 3;
	return (1);
}

static int	ft_small_token(t_main *mn, t_list *lst, char *s)
{
	if (lst->next)
		s = lst->next->content;
	else
		s = NULL;
	if (!s)
		return (ft_error_tocken(mn, 2, "newline"));
	else if (*s == '>' || *s == ';' || *s == '|')
		return (ft_error_tocken(mn, 2, s));
	return (1);
}

static int	ft_big_token(t_main *mn, t_list *lst, char *s)
{
	if (lst->next)
		s = lst->next->content;
	else
		s = NULL;
	if (!s)
		return (ft_error_tocken(mn, 2, "newline"));
	else if (*s == '<' || *s == ';' || *s == '|')
		return (ft_error_tocken(mn, 2, s));
	if (*s == '>')
	{
		lst = lst->next;
		if (lst->next)
			s = lst->next->content;
		else
			s = NULL;
		if (!s)
			return (ft_error_tocken(mn, 2, "newline"));
		else if (*s == '<' || *s == ';' || *s == '|')
			return (ft_error_tocken(mn, 2, s));
	}
	return (1);
}

int			ft_check_tockens(t_main *mn)
{
	t_list	*lst;
	char	*s;
	int		i;

	i = 0;
	lst = mn->lexer;
	if (ft_strncmp(lst->content, ";", 1) == 0 && lst->next
		&& ft_strncmp(lst->next->content, ";", 1) != 0)
		return (ft_error_tocken(mn, 2, ";"));
	while (lst)
	{
		s = lst->content;
		if (*s == ';' && ft_semicol_token(mn, lst, s, &i) < 0)
			return (-1);
		else if (*s == '|' && ft_pipe_token(mn, lst, s, &i) < 0)
			return (-1);
		else if (*s == '<' && ft_small_token(mn, lst, s) < 0)
			return (-1);
		else if (*s == '>' && ft_big_token(mn, lst, s) < 0)
			return (-1);
		else
			i = 1;
		lst = lst->next;
	}
	return (1);
}
