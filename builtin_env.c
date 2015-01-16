/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 14:25:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/16 13:52:51 by ngoguey          ###   ########.fr       */
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

void		msh_print_env(t_mshc *msh, int fd)
{
	const char	**env = (msh != NULL) ? (const char**)msh->env : NULL;

	if (env == NULL)
		return ;
	while (*env != NULL)
	{
		ft_dprintf(fd, "%s\n", *env);
		env++;
	}
	return ;
}

void		msh_builtin_env(t_msh *msh, t_cmd *cmd)
{
	int		fd_saves[2];

	if (msh_builtin_init_fds(msh, cmd, fd_saves))
		return ;
	msh_print_env(msh, 1);
	msh_builtin_disable_fds(msh, cmd, fd_saves);
	return ;
}
