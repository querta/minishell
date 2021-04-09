/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:17:46 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 21:33:26 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quit(int sig)
{
	(void)sig;
}

void	ft_signal(int sig)
{
	char	*b;

	b = NULL;
	if (sig == 2 && g_mn->pid == 1)
	{
		ft_putstr_fd("\nminishell$ ", 1);
		b = g_mn->str;
		g_mn->str = ft_strdup("");
		free(b);
		g_mn->n_count = 0;
		g_mn->cursor = g_mn->n_count + (int)ft_strlen(g_mn->name_shell);
	}
	if (sig == 2 && g_mn->pid == 0)
		ft_putstr_fd("\n", 1);
	if (sig == 3 && g_mn->pid == 0)
		ft_putstr_fd("Quit: 3\n", 1);
}
