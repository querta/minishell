/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:45:01 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:24:17 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rec_chr(int n, int fd)
{
	int	i;

	i = 0;
	if ((n / 10) > 0)
		i = rec_chr((n / 10), fd);
	else
	{
		i = n + 48;
		write(fd, &i, 1);
		return (n);
	}
	i = n - (i * 10) + 48;
	write(fd, &i, 1);
	return (n);
}

static int	min_int(int n, int fd)
{
	write(fd, "2", 1);
	n += 2000000000;
	return (n);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n && fd >= 0)
	{
		if (n < 0 && (n * -1) != 0)
		{
			write(fd, "-", 1);
			if (n == -2147483648)
				n = min_int(n, fd);
			n *= -1;
		}
		else if (n < 0 && (n * -1) == 0)
			write(fd, "0", 1);
		if (n > 0)
		{
			if ((n / 10) == 0)
			{
				n += 48;
				write(fd, &n, 1);
			}
			else
				rec_chr(n, fd);
		}
	}
	else if (!n && fd >= 0)
		write(fd, "0", 1);
}
