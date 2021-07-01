/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:32:52 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 21:39:51 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_text(t_main *mn, char *buff)
{
	char	*loc;
	char	*br;
	int		ret;

	ret = 0;
	if ((br = ft_strchr(buff, '\n')))
	{
		*br = 0;
		ret = 1;
	}
	loc = mn->str;
	if (!(mn->str = ft_strjoin(mn->str, buff)))
	{
		free(loc);
		return (-1);
	}
	free(loc);
	return (ret);
}

static void	ft_pre_gnl(t_main *mn)
{
	char	*b;
	char	buf[10];

	b = buf;
	ft_noncanon_mode();
	tgetent(0, getenv("TERM"));
	tputs(tgetstr("sc", &b), 1, ft_int);
	mn->str = ft_strdup("");
	mn->cursor = mn->n_count + (int)ft_strlen(mn->name_shell);
	write(1, mn->name_shell, (int)ft_strlen(mn->name_shell));
}

static int	ft_returner(int fd_r, int *i)
{
	*i = 0;
	ft_canon_mode();
	return (fd_r);
}

static int	buffer_checker(t_main *mn)
{
	char	buff[6];
	int		fd_r;

	ft_pre_gnl(mn);
	while ((fd_r = read(0, buff, 5)))
	{
		buff[fd_r] = 0;
		if (*buff == 4 && fd_r == 1 && ft_strlen(mn->str) == 0)
			break ;
		if ((*buff == 127 && fd_r == 1) || fd_r == 3)
		{
			if (ft_specsymb_operator(mn, buff, fd_r) < 0)
				return (ft_returner(-1, &mn->n_count));
		}
		else if ((fd_r < 2 && (*buff > 31 || *buff == 10 || *buff < 0)))
		{
			mn->cursor += fd_r;
			write(1, buff, fd_r);
			if ((fd_r = end_text(mn, buff)) != 0)
				return (ft_returner(fd_r, &mn->n_count));
		}
	}
	return (ft_returner(-2, &mn->n_count));
}

int			get_next_line(int fd, t_main *mn)
{
	int				ret;

	ret = 0;
	if (fd < 0)
		return (-1);
	return (buffer_checker(mn));
}
