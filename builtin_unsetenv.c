/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 11:03:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 11:27:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_builtin_unsetenv(t_msh *msh, t_cmd *cmd)
{
	int		fd_saves[2];
	char	**ptr;

	if (msh_builtin_init_fds(msh, cmd, fd_saves))
		return ;
	if (cmd->cmdav[1] == NULL)
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
	else
	{
		ptr = cmd->cmdav + 1;
		while (*ptr != NULL)
			(void)msh_del_envk(msh, *ptr++);
	}
	msh_builtin_disable_fds(msh, cmd, fd_saves);
	return ;
}
