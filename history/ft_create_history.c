/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:30:27 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:58:55 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_save_history(t_main *mn)
{
	if (mn->dir_hstry[1] > 0 || mn->sum_hstry > 501)
		ft_more_elements_history(mn);
	else
		ft_elements_history(mn);
	mn->c_hstry = 0;
	while (mn->c_hstry <= mn->sum_hstry)
		free(mn->hstry[mn->c_hstry++]);
}

static void	ft_ref_hstry(t_main *mn, char *str)
{
	mn->c_hstry = 0;
	while (++mn->c_hstry < 501)
	{
		str = mn->hstry[mn->c_hstry];
		mn->hstry[mn->c_hstry] = mn->hstry[mn->c_hstry + 500];
		free(str);
	}
	mn->dir_hstry[0] = 0;
	mn->sum_hstry = 501;
	mn->dir_hstry[1]++;
}

void		ft_refresh_hstry(t_main *mn)
{
	char *str;

	str = NULL;
	if (!mn->str)
		return ;
	if (ft_strlen(mn->str) == 0)
	{
		free(mn->str);
		return ;
	}
	str = mn->hstry[mn->sum_hstry];
	if (!(mn->hstry[mn->sum_hstry] = ft_strdup(mn->str)))
		return ;
	free(str);
	if (++mn->sum_hstry > 501)
		mn->dir_hstry[0] = mn->sum_hstry - 501;
	if (mn->dir_hstry[0] == 500)
		ft_ref_hstry(mn, str);
	if (!(mn->hstry[mn->sum_hstry] = ft_strdup("")))
		return ;
	mn->c_hstry = mn->sum_hstry;
}

int			ft_create_hstry_in_main(t_main *mn)
{
	int		fd;
	char	*s;

	s = NULL;
	if ((fd = open("./.bash_history", O_CREAT | O_RDWR | O_APPEND, 416)) < 0)
		return (-1);
	mn->c_hstry = 0;
	mn->hstry[mn->c_hstry++] = ft_strdup("");
	while ((get_next_line_classic(fd, &s)) > 0)
	{
		if (!(mn->hstry[mn->c_hstry] = ft_strdup(s)))
			return (ft_error_sschar(mn->hstry, mn->c_hstry, s));
		free(s);
		mn->c_hstry++;
	}
	mn->hstry[mn->c_hstry] = ft_strdup(s);
	free(s);
	mn->sum_hstry = mn->c_hstry;
	close(fd);
	return (1);
}
