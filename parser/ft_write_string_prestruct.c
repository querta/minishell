/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_string_prestruct.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:33:44 by spitt             #+#    #+#             */
/*   Updated: 2021/04/07 15:39:08 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_woquot_convert_write(t_main *mn, char *src, int *d)
{
	int	i;

	i = d[0];
	while (src[mn->car] != 0 && ft_the_razdelitel(src[mn->car]) != 1)
	{
		if (src[mn->car] == 36)
			i = ft_from_env_write(mn, i, src);
		else if (src[mn->car] == 92)
			mn->str[i++] = src[++mn->car];
		else
			mn->str[i++] = src[mn->car];
		mn->car++;
	}
	d[0] = i;
	if (ft_the_razdelitel(src[mn->car]) == 1)
		return (mn->car - 1);
	return (-1);
}

static int	ft_dquot_convert_write(t_main *mn, char *src, int *d)
{
	int	i;

	i = *d;
	mn->car++;
	while (src[mn->car] && src[mn->car] != 34)
	{
		if (src[mn->car] == 36)
			i = ft_from_env_write(mn, i, src);
		else if (src[mn->car] == 92 && (src[mn->car + 1] == 36 ||
				src[mn->car + 1] == 34 || src[mn->car + 1] == 92))
			mn->str[i++] = src[++mn->car];
		else
			mn->str[i++] = src[mn->car];
		mn->car++;
	}
	*d = i;
	if (src[mn->car] == 34)
		return (mn->car);
	return (-1);
}

static int	ft_quot_convert_write(t_main *mn, char *src, int *d)
{
	int	i;

	i = *d;
	mn->car++;
	while (src[mn->car] && src[mn->car] != 39)
	{
		mn->str[i] = src[mn->car];
		i++;
		mn->car++;
	}
	*d = i;
	if (src[mn->car] == 39)
		return (mn->car);
	return (-1);
}

int			ft_write_new_string(t_main *mn, t_list **lst, int len, char *str)
{
	int		i;
	t_list	*new;

	mn->car = -1;
	i = 0;
	if (len < 2)
		len = 1;
	if (!(mn->str = ft_calloc(len + 1, 1)))
		return (ft_errors(0));
	while (str && i < len && ++mn->car > -1)
	{
		if (str[mn->car] == 39)
			mn->car = ft_quot_convert_write(mn, str, &i);
		else if (str[mn->car] == 34)
			mn->car = ft_dquot_convert_write(mn, str, &i);
		else
			mn->car = ft_woquot_convert_write(mn, str, &i);
		if (mn->car == -1)
			mn->car = -2;
	}
	free(str);
	if (!(new = ft_lstnew(mn->str)))
		return (-1);
	ft_lstadd_back(lst, new);
	return (1);
}
