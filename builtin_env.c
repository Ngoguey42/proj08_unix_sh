/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 14:25:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 11:06:21 by ngoguey          ###   ########.fr       */
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

void		msh_print_env(const t_msh *msh, int fd)
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
	int		fd1_save;

	fd1_save = -1;
	if (msh_bi_init_pipeout(msh, cmd, &fd1_save))
	{
		msh_bi_disable_pipeout(msh, cmd, fd1_save);
		return ;
	}
	if (msh_bi_init_redirs(msh, *cmd->ared))
	{
		msh_bi_disable_redirs(msh, *cmd->ared);
		msh_bi_disable_pipeout(msh, cmd, fd1_save);
		return ;
	}
	msh_print_env(msh, 1);
	msh_bi_disable_redirs(msh, *cmd->ared);
	msh_bi_disable_pipeout(msh, cmd, fd1_save);
	return ;
}
