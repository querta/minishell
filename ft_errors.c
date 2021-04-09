/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:02:32 by spitt             #+#    #+#             */
/*   Updated: 2021/04/06 19:07:55 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_errors(int s)
{
	if (s == 0)
		ft_putendl_fd("memory error", 1);
	if (s == 1)
		ft_putendl_fd("rdir error", 1);
	if (s == 2)
		ft_putendl_fd("tocken error", 1);
	if (s == 3)
		ft_putendl_fd("pipe error", 1);
	return (-1);
}

void	*ft_null_error(int s, t_main *mn, void *str)
{
	if (str)
		free(str);
	if (s == 0)
	{
		write(1, mn->name_shell, ft_strlen(mn->name_shell) - 2);
		write(1, ": syntax error near unexpected token `;;'\n", 42);
		mn->err = 258;
	}
	if (s == 1)
	{
		write(1, mn->name_shell, ft_strlen(mn->name_shell) - 2);
		write(1, ": syntax error near unexpected token `||'\n", 42);
		mn->err = 258;
	}
	if (s == 2)
	{
		write(1, mn->name_shell, ft_strlen(mn->name_shell) - 2);
		write(1, ": syntax error near unexpected token `newline'\n", 47);
		mn->err = 258;
	}
	if (s == 3)
		ft_putendl_fd("memory error NULL", 1);
	return (NULL);
}

int		ft_error_sschar(char **str, int i, char *s)
{
	i -= 1;
	while (i >= 0)
	{
		free(str[i--]);
	}
	free(s);
	return (-1);
}

void	error_var(t_main *mn, char *cmd, char *arg)
{
	write(2, mn->name_shell, ft_strlen(mn->name_shell) - 2);
	write(2, ": ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, ": `", 3);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	mn->err = 1;
}

int		ft_error_tocken(t_main *mn, int sig, char *c)
{
	write(1, mn->name_shell, ft_strlen(mn->name_shell) - 2);
	if (sig == 0)
		write(1, ": syntax error near unexpected token `;;'\n", 42);
	else if (sig == 1)
		write(1, ": syntax error near unexpected token `||'\n", 42);
	else if (sig == 2)
	{
		write(1, ": syntax error near unexpected token ", 37);
		write(1, "'", 1);
		write(1, c, ft_strlen(c));
		write(1, "'\n", 2);
	}
	mn->err = 258;
	return (-1);
}
