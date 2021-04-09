/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:21:49 by spitt             #+#    #+#             */
/*   Updated: 2021/04/06 11:46:31 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_up_history(t_main *mn, char *b)
{
	char	*s;

	s = NULL;
	if (mn->c_hstry - 1 == 0)
		return ;
	if (mn->c_hstry == mn->sum_hstry)
	{
		s = mn->hstry[mn->c_hstry];
		mn->hstry[mn->c_hstry] = ft_strdup(mn->str);
		free(s);
		if (!mn->hstry[mn->c_hstry])
			return ;
	}
	mn->c_hstry--;
	tputs(tgetstr("rc", &b), 1, ft_int);
	tputs(tgetstr("cd", &b), 1, ft_int);
	write(1, mn->name_shell, (int)ft_strlen(mn->name_shell));
	s = mn->str;
	mn->str = ft_strdup(mn->hstry[mn->c_hstry]);
	free(s);
	if (!mn->hstry[mn->c_hstry])
		return ;
	write(1, mn->str, (int)ft_strlen(mn->str));
	mn->cursor = mn->n_count + (int)(ft_strlen(mn->name_shell) +
					(int)ft_strlen(mn->str));
}

static void	ft_down_history(t_main *mn, char *b)
{
	char	*s;

	s = NULL;
	if (mn->c_hstry == mn->sum_hstry)
		return ;
	tputs(tgetstr("rc", &b), 1, ft_int);
	tputs(tgetstr("cd", &b), 1, ft_int);
	write(1, mn->name_shell, (int)ft_strlen(mn->name_shell));
	s = mn->str;
	mn->str = ft_strdup(mn->hstry[++mn->c_hstry]);
	free(s);
	if (!mn->hstry[mn->c_hstry])
		return ;
	write(1, mn->str, ft_strlen(mn->str));
	mn->cursor = mn->n_count + (int)ft_strlen(mn->name_shell) +
					(int)ft_strlen(mn->str);
}

static void	ft_backspace_presskey(t_main *mn, char *b)
{
	int	i;

	i = 0;
	if (mn->cursor > (mn->n_count + (int)ft_strlen(mn->name_shell)))
	{
		mn->str[((int)ft_strlen(mn->str) - 1)] = 0;
		mn->cursor--;
		if ((mn->n_count + (int)ft_strlen(mn->name_shell) +
			(int)ft_strlen(mn->str)) % tgetnum("co") == tgetnum("co") - 1)
		{
			i = 0;
			while (i++ <= tgetnum("co") + 1)
				tputs(tgetstr("nb", &b), 1, ft_int);
		}
		tputs(tgetstr("le", &b), 1, ft_int);
		tputs(tgetstr("dc", &b), 1, ft_int);
		tputs(tgetstr("dc", &b), 1, ft_int);
	}
}

int			ft_specsymb_operator(t_main *mn, char *buff, int fd_r)
{
	char *b;
	char buf[10];

	b = buf;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65)
		ft_up_history(mn, b);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66)
		ft_down_history(mn, b);
	else if (buff[0] == 127 && fd_r == 1)
		ft_backspace_presskey(mn, b);
	if (!mn->str)
		return (ft_errors(0));
	return (1);
}
