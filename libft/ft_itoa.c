/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:04:45 by spitt             #+#    #+#             */
/*   Updated: 2020/11/11 12:28:07 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i = 1;
		n *= -1;
	}
	if ((n / 10) == 0)
		return (1);
	i += ft_nbrlen(n / 10);
	return (i + 1);
}

static int	new_str(char *str, int n)
{
	int	i;

	if ((n / 10) == 0)
	{
		if (n < 0)
		{
			str[0] = '-';
			str[1] = (n * -1) + 48;
			return (2);
		}
		else
		{
			str[0] = n + 48;
			return (1);
		}
	}
	if (n < 0)
	{
		i = new_str(str, (n / 10));
		n *= -1;
	}
	else
		i = new_str(str, (n / 10));
	str[i] = (n % 10) + 48;
	return (i + 1);
}

char		*ft_itoa(int n)
{
	char	*ret_str;
	int		i;

	if (n == -2147483648)
		ret_str = malloc(ft_nbrlen(n / 10) + 2);
	else
		ret_str = malloc(ft_nbrlen(n) + 1);
	if (ret_str == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		i = new_str(ret_str, (n / 10));
		ret_str[i] = '8';
		i++;
	}
	else
		i = new_str(ret_str, n);
	ret_str[i] = '\0';
	return (ret_str);
}
