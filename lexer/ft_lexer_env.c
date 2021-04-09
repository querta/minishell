/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:04:56 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 18:03:36 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_full_write(t_main *mn)
{
	t_list	*new_lex;
	char	*new_str;

	if (!(new_str = ft_strdup(&mn->str[mn->car])))
		return (ft_errors(0));
	if (!(new_lex = ft_lstnew(new_str)))
		return (ft_errors(0));
	ft_lstadd_back(&mn->lexer, new_lex);
	return (1);
}

int			ft_new_line_write(t_main *mn, int last_char)
{
	char	c;

	c = mn->str[last_char];
	mn->str[last_char] = 0;
	if ((ft_full_write(mn)) < 0)
		return (-1);
	mn->str[last_char] = c;
	if (c == ' ')
		mn->car = last_char + 1;
	else
		mn->car = last_char;
	return (1);
}

int			ft_cmp_after_while(t_main *mn, int last_char)
{
	if (last_char == mn->car)
		return (1);
	if (!mn->str[last_char])
	{
		if ((ft_full_write(mn)) < 0)
			return (-1);
		mn->car = last_char;
	}
	else
	{
		if (ft_new_line_write(mn, last_char) < 0)
			return (-1);
	}
	return (1);
}

int			ft_err_with_free(int i, char *s)
{
	free(s);
	return (ft_errors(i));
}
