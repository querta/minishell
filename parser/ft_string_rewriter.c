/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_rewriter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:02:22 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:03:53 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_print_symbs(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) ||
			(c > 96 && c < 123) || c == 95)
		return (1);
	return (0);
}

int			ft_specsymb_searcher(int c)
{
	if (c == '.' || c == '/' || c == '$' || c == 92 ||
		c == 39 || c == 34 || c == ';' || c == '|' ||
		c == 32 || c == ':' || c == '!' || c == '?' ||
		c == 60 || c == 62 || c == '*' || c == '[' ||
		c == ']' || c == '~' || c == '&')
		return (1);
	return (0);
}

int			ft_the_razdelitel(int c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

static void	ft_clean_lexer(t_main *mn)
{
	t_list	*lst_2;

	lst_2 = NULL;
	while (mn->lexer && ft_strncmp(mn->lexer->content, ";", 1) != 0)
	{
		lst_2 = mn->lexer->next;
		free(mn->lexer);
		mn->lexer = lst_2;
	}
	if (mn->lexer)
	{
		lst_2 = mn->lexer->next;
		free(mn->lexer->content);
		free(mn->lexer);
		mn->lexer = lst_2;
	}
}

t_list		*ft_string_rewriter(t_main *mn)
{
	int		len_str;
	t_list	*lst;
	t_list	*new_lex;

	lst = mn->lexer;
	new_lex = NULL;
	while (lst && ft_strncmp(lst->content, ";", 1) != 0)
	{
		mn->str = lst->content;
		len_str = 0;
		if (mn->str[0] != 60 || mn->str[0] != 62 ||
			mn->str[0] != 124)
		{
			len_str = ft_lenght_new_string(mn) + 1;
			if (ft_write_new_string(mn, &new_lex, len_str, lst->content) < 0)
				return (NULL);
		}
		lst = lst->next;
	}
	ft_clean_lexer(mn);
	return (new_lex);
}
