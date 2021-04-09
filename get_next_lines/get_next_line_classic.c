/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_classic.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:32:52 by spitt             #+#    #+#             */
/*   Updated: 2021/03/25 17:19:00 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ten_in_static(char **st, char **line)
{
	char	*loc;
	char	*br;

	if (*st == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((br = ft_strchr(*st, '\n')))
	{
		*br = 0;
		if (!(*line = ft_strdup(*st)))
			return (-1);
		loc = *st;
		if (!(*st = ft_strdup(++br)))
		{
			free(loc);
			return (-1);
		}
		free(loc);
		return (1);
	}
	*line = (*st);
	(*st) = 0;
	return (0);
}

static int	end_text(char **st, char **line, char **buff)
{
	char	*loc;
	char	*br;
	int		ret;

	ret = 0;
	if ((br = ft_strchr(*buff, '\n')))
	{
		*br = 0;
		loc = *st;
		if (!(*st = ft_strdup(++br)))
		{
			free(loc);
			return (-1);
		}
		free(loc);
		ret = 1;
	}
	loc = *line;
	if (!(*line = ft_strjoin(*line, *buff)))
	{
		free(loc);
		return (-1);
	}
	free(loc);
	return (ret);
}

static int	buffer_checker(char **st, char **line, char fd)
{
	char	*buff;
	int		fd_r;

	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((fd_r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[fd_r] = 0;
		if ((fd_r = end_text(st, line, &buff)) != 0)
		{
			free(buff);
			return (fd_r);
		}
	}
	free(buff);
	return (0);
}

int			get_next_line_classic(int fd, char **line)
{
	static char	*st[1025];
	int			ret;

	ret = 0;
	if (BUFFER_SIZE < 1 || !line || read(fd, 0, 0))
		return (-1);
	if ((ret = ten_in_static(&st[fd], line)) == 0)
		return (buffer_checker(&st[fd], line, fd));
	return (ret);
}
