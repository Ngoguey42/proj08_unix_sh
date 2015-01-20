/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 10:35:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 11:03:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_env(t_msh *msh, t_cmd *cmd)
{
	char	*k;
	char	*v;

	k = cmd->cmdav[1];
	v = cmd->cmdav[2];
	if (v == NULL)
		v = "";
	(void)msh_update_envkv_m(msh, k, v);
	return ;
}

void		msh_builtin_setenv(t_msh *msh, t_cmd *cmd)
{
	int		fd_saves[2];

	if (msh_builtin_init_fds(msh, cmd, fd_saves))
		return ;
	if (cmd->cmdav[1] == NULL)
		msh_print_env(msh, 1);
	else if (cmd->cmdav[2] == NULL || cmd->cmdav[3] == NULL)
		set_env(msh, cmd);
	else
		ft_dprintf(2, "setenv: Too many arguments.\n");
	msh_builtin_disable_fds(msh, cmd, fd_saves);
	return ;
}
