/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 14:25:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/05 08:58:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

/*
** 'msh_print_env' prints env, for debug or 'env' builtin call.
** *
** 'msh_builtin_env' 'env' builtin. Handles pipes, redirections and options.
*/

static void	print_locvars(const t_list *lst, int fd)
{
	while (lst)
	{
/* 		D(char*, lst->content); */
		ft_dprintf(fd, "%s\n", (char*)lst->content);		
		lst = lst->next;
	}
	return ;
}

void		msh_print_env(t_mshc *msh, const t_cmd *cmd, int fd)
{
	const char	**env = (msh != NULL) ? (const char**)msh->env : NULL;

	if (env != NULL && (!cmd || cmd->ignore_env == false))
	{
		while (*env != NULL)
		{
/* 			D(char*, *env); */
			if (cmd == NULL || !msh_isin_locvars(*env, *cmd->alvar))
				ft_dprintf(fd, "%s\n", *env);
			env++;
		}
	}
	if (cmd)
		print_locvars(*cmd->alvar, fd);
	return ;
}

void		msh_builtin_env(t_msh *msh, t_cmd *cmd)
{
	int		fd_saves[2];

	if (msh_builtin_init_fds(msh, cmd, fd_saves))
		return ;
	msh_print_env(msh, cmd, 1);
	msh_builtin_disable_fds(msh, cmd, fd_saves);
	return ;
}
