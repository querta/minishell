/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_string_prestruct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:29:50 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 14:10:06 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_woquot_convert_len(t_main *mn, int *len)
{
	while (mn->str[mn->car] != 0 && ft_the_razdelitel(mn->str[mn->car]) != 1)
	{
		if (mn->str[mn->car] == 36)
			*len += ft_from_env_len(mn);
		else if (mn->str[mn->car] == 92)
		{
			*len += 1;
			mn->car++;
		}
		else
			*len += 1;
		mn->car++;
	}
	if (ft_the_razdelitel(mn->str[mn->car]) == 1)
		return (mn->car - 1);
	return (-1);
}

static int	ft_dquot_convert_len(t_main *mn, int *len)
{
	mn->car++;
	while (mn->str[mn->car] && mn->str[mn->car] != 34)
	{
		if (mn->str[mn->car] == 36)
			*len += ft_from_env_len(mn);
		else if (mn->str[mn->car] == 92 && (mn->str[mn->car + 1] == 36 ||
				mn->str[mn->car + 1] == 34 || mn->str[mn->car + 1] == 92))
		{
			*len += 1;
			mn->car += 1;
		}
		else
			*len += 1;
		mn->car++;
	}
	if (mn->str[mn->car] == 34)
		return (mn->car);
	return (-1);
}

static int	ft_quot_convert_len(t_main *mn, int *len)
{
	mn->car++;
	while (mn->str[mn->car] && mn->str[mn->car] != 39)
	{
		*len += 1;
		mn->car++;
	}
	if (mn->str[mn->car] == 39)
		return (mn->car);
	return (-1);
}

int			ft_lenght_new_string(t_main *mn)
{
	int	len_str;

	mn->car = 0;
	len_str = 0;
	while (mn->str && mn->car < (int)ft_strlen(mn->str))
	{
		if (mn->str[mn->car] == 39)
			mn->car = ft_quot_convert_len(mn, &len_str);
		else if (mn->str[mn->car] == 34)
			mn->car = ft_dquot_convert_len(mn, &len_str);
		else
			mn->car = ft_woquot_convert_len(mn, &len_str);
		if (mn->car == -1)
			break ;
		mn->car++;
	}
	return (len_str);
}
