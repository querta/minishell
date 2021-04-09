/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonte <mmonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:30:08 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/06 18:03:28 by mmonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env(t_main *mn, int i)
{
	int k;

	k = 0;
	free(mn->envp[i]);
	while (mn->envp[i])
	{
		mn->envp[i] = mn->envp[i + 1];
		i++;
	}
	free(mn->envp[i]);
}

void		run_unset(t_main *mn, t_pipe *piptmp)
{
	t_rdir	*rdir;
	int		i;

	rdir = piptmp->redir;
	if (rdir->into_arg)
	{
		if (!(ft_strncmp(rdir->sc, "unset=", 6) == 0))
		{
			i = 0;
			while (i < rdir->into_arg)
			{
				if (validate_var_str(rdir->arg[i], 0))
				{
					if (search_env_index(mn, rdir->arg[i]) != -1)
						del_env(mn, search_env_index(mn, rdir->arg[i]));
				}
				else
					error_var(mn, "unset", rdir->arg[i]);
				i++;
			}
		}
	}
}
