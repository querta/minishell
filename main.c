/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:47:54 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 21:23:33 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		main_starter(t_main *mn)
{
	t_list	*next;

	next = NULL;
	while (mn->lexer)
	{
		next = mn->lexer->next;
		free(mn->lexer->content);
		free(mn->lexer);
		mn->lexer = next;
	}
	mn->ap_flag = 0;
	mn->dap_flag = 0;
	mn->car = 0;
	mn->rdir_acc = 0;
	mn->pid = 1;
	mn->temp0fd = dup(0);
}

static t_main	*main_creater(char **envp, char *name_shell)
{
	struct termios	tios;

	if (!(g_mn = ft_calloc(1, sizeof(t_main))))
		exit(1);
	ft_create_hstry_in_main(g_mn);
	g_mn->envp = addtoarr(envp, 0);
	g_mn->pid = 1;
	if (!(g_mn->name_shell = ft_strjoin((ft_strrchr(name_shell, '/')
			+ 1), "$ ")))
	{
		free(g_mn);
		exit(1);
	}
	tcgetattr(0, &tios);
	g_mn->term = tios;
	return (g_mn);
}

int				main(int argc, char **argv, char **envp)
{
	(void)argc;
	if (!(g_mn = main_creater(envp, argv[0])))
		exit(0);
	while (1)
	{
		signal(SIGINT, ft_signal);
		signal(SIGQUIT, ft_signal);
		ft_refresh_hstry(g_mn);
		lexer_parser(g_mn);
		main_starter(g_mn);
		if (get_next_line(0, g_mn) == -2)
			ft_exit(g_mn, NULL, 0);
	}
	ft_exit(g_mn, g_mn->job->pipe, 0);
}
