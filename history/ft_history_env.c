/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:22:56 by spitt             #+#    #+#             */
/*   Updated: 2021/04/06 11:23:36 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_more_elements_history(t_main *mn)
{
	int	fd;

	fd = 0;
	mn->c_hstry = mn->dir_hstry[0];
	if ((fd = open("./.bash_history", O_CREAT | O_WRONLY, 416)) < 0)
		return ;
	while (++mn->c_hstry < mn->sum_hstry)
	{
		write(fd, mn->hstry[mn->c_hstry],
				(int)ft_strlen(mn->hstry[mn->c_hstry]));
		write(fd, "\n", 1);
	}
	close(fd);
}

void		ft_elements_history(t_main *mn)
{
	int	fd;

	fd = 0;
	mn->c_hstry = 0;
	if ((fd = open("./.bash_history", O_CREAT | O_WRONLY, 416)) < 0)
		return ;
	while (++mn->c_hstry < mn->sum_hstry)
	{
		write(fd, mn->hstry[mn->c_hstry],
				(int)ft_strlen(mn->hstry[mn->c_hstry]));
		write(fd, "\n", 1);
	}
	close(fd);
}
