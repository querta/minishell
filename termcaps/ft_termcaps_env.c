/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:43:42 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 13:39:34 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_canon_mode(void)
{
	struct termios tios;

	tios = g_mn->term;
	tcsetattr(0, TCSANOW, &tios);
	return ;
}

void	ft_noncanon_mode(void)
{
	struct termios tios;

	tios = g_mn->term;
	tios.c_lflag &= ~(ECHO);
	tios.c_lflag &= ~(ICANON);
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &tios);
	return ;
}

int		ft_int(int i)
{
	return (write(0, &i, 1));
}
