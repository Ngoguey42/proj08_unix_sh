/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 10:27:42 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 10:29:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

void		msh_builtin_exit(t_msh *msh, t_cmd *cmd)
{
	int	fd_saves[2];

	(void)msh_builtin_init_fds(msh, cmd, fd_saves);
	ft_putendl("exit");
	exit(0);
	return ;
}
