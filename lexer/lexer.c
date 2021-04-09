/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:01:59 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 18:17:51 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*spec_symbol_writer_cont(t_main *mn, int last_char)
{
	if (mn->str[last_char] == 62)
		return (ft_strdup(">"));
	else if (mn->str[last_char] == 60)
		return (ft_strdup("<"));
	else if (mn->str[last_char] == 124)
		return (ft_strdup("|"));
	else if (mn->str[last_char] == 59)
		return (ft_strdup(";"));
	return (NULL);
}

static int	spec_symbols_writer(t_main *mn, int last_char)
{
	char	*new_str;
	t_list	*lex;

	lex = NULL;
	new_str = NULL;
	if (last_char != mn->car)
	{
		if ((ft_new_line_write(mn, last_char)) < 0)
			return (-1);
	}
	else
		mn->car++;
	if (mn->str[last_char - 1] != 92)
	{
		if (!(new_str = spec_symbol_writer_cont(mn, last_char)))
			return (ft_errors(0));
	}
	if (!(lex = ft_lstnew(new_str)))
		return (ft_err_with_free(0, new_str));
	ft_lstadd_back(&mn->lexer, lex);
	last_char++;
	while (ft_isspace(mn->str[last_char]) != 0)
		last_char++;
	mn->car = last_char;
	return (last_char);
}

static int	ft_cmp_quats_cont(t_main *mn, int last_char)
{
	if (mn->str[last_char] == 34 && mn->ap_flag == 0 &&
		mn->dap_flag == 0 && (last_char - 1) > -1 &&
		mn->str[last_char - 1] != 92)
		mn->dap_flag = 1;
	else if (mn->str[last_char] == 39 && mn->ap_flag == 0 &&
		mn->dap_flag == 0 && (last_char - 1) > -1 &&
		mn->str[last_char - 1] != 92)
		mn->ap_flag = 1;
	else if (mn->str[last_char] == 34 && mn->ap_flag == 0 &&
		mn->dap_flag == 1 && (last_char - 1) > -1 &&
		mn->str[last_char - 1] != 92)
		mn->dap_flag = 0;
	else if (mn->str[last_char] == 39 && mn->ap_flag == 1 &&
		mn->dap_flag == 0)
		mn->ap_flag = 0;
	return (last_char);
}

static int	ft_cmp_quats(t_main *mn, int *lc)
{
	int	last_char;

	last_char = lc[0];
	while ((mn->str[last_char] == 62 || mn->str[last_char] == 60 ||
		mn->str[last_char] == 59 || mn->str[last_char] == 124)
		&& mn->ap_flag == 0 && mn->dap_flag == 0 && last_char > 0 &&
		mn->str[last_char - 1] != 92)
		last_char = spec_symbols_writer(mn, last_char);
	if (last_char < 0)
		return (-1);
	if (!mn->str[last_char])
	{
		lc[0] = last_char - 1;
		return (1);
	}
	if ((mn->str[last_char] == ' ' || mn->str[last_char] == ';' ||
		mn->str[last_char] == '|' || mn->str[last_char] == '>' ||
		mn->str[last_char] == '<') && mn->ap_flag == 0 &&
		mn->dap_flag == 0 && last_char > 0 && mn->str[last_char - 1] != 92)
		return (0);
	else
		last_char = ft_cmp_quats_cont(mn, last_char);
	lc[0] = last_char;
	return (1);
}

int			lexer_parser(t_main *mn)
{
	int		c[2];

	c[0] = 0;
	c[1] = 0;
	if (!mn->str || (mn->str && ft_strlen(mn->str) == 0))
		return (1);
	while (mn->str[mn->car])
	{
		while ((ft_isspace(mn->str[mn->car])) != 0)
			mn->car++;
		c[0] = mn->car - 1;
		while (mn->str[++c[0]])
		{
			if ((c[1] = ft_cmp_quats(mn, &c[0]) < 1))
				break ;
		}
		if (c[1] == -1 || (c[1] != -1 && ft_cmp_after_while(mn, c[0]) < 0))
			return (1);
	}
	mn->car = 0;
	free(mn->str);
	if (ft_check_tockens(mn) < 0)
		return (-1);
	return (parser_shell(mn));
}
