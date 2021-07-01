/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:03:30 by spitt             #+#    #+#             */
/*   Updated: 2021/01/27 19:07:10 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ret(int flag, int minus, int ret_val)
{
	if (flag - 1 > 10 && minus > 0)
		return (-1);
	if (flag - 1 > 10 && minus < 0)
		return (0);
	return (ret_val * minus);
}

static int	digit(int i, char str, int *flag)
{
	flag[0] += 1;
	if (i == 0 && (int)str == 48)
		return (0);
	else if (i != 0 && (int)str == 48)
		return (i *= 10);
	else
	{
		i *= 10;
		i += ((int)str - 48);
		return (i);
	}
}

static void	pre_digit(int *flag, int *minus, char str)
{
	if (str == 45)
		minus[0] *= -1;
	flag[0] += 1;
}

int			ft_atoi(const char *str)
{
	int				flag;
	unsigned int	i;
	int				ret_val;
	int				minus;

	flag = 0;
	i = 0;
	ret_val = 0;
	minus = 1;
	while (str[i] != 0)
	{
		if (((int)str[i] == 45 || str[i] == 43) && flag == 0)
			pre_digit(&flag, &minus, str[i]);
		else if (flag == 0 && (str[i] == '\t' || str[i] == '\n' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
			flag = 0;
		else if ((int)str[i] > 47 && (int)str[i] < 58)
			ret_val = digit(ret_val, str[i], &flag);
		else
			break ;
		i++;
	}
	return (ret(flag, minus, ret_val));
}
