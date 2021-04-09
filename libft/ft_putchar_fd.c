/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:19:24 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:34:45 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	unicode_writer(char c, int fd)
{
	char byte[2];

	byte[1] = (c & 0x3F) | 0x80;
	byte[0] = ((c & 0xC0) >> 6) | 0xC0;
	write(fd, byte, 2);
}

void		ft_putchar_fd(char c, int fd)
{
	if (c < 0 && fd >= 0)
		unicode_writer(c, fd);
	else if (c >= 0 && fd >= 0)
		write(fd, &c, 1);
}
