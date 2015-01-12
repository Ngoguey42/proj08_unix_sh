/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cc_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 08:15:26 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/09 14:29:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

/*
** Builtins Command Center, pipes.
*/
/*
** 'msh_bi_init_pipeout' initiates stdout before a pipe-out.
**			'dup' => closed in 'msh_bi_disable_pipeout'.
**			'dup2' => closed in 'msh_bi_disable_pipeout'.
** *
** 'msh_bi_disable_pipeout' restores stdout after a pipe-out.
**			'dup2' => closed on next 'msh_bi_init_pipeout' OR msh exit.
** *
*/

int			msh_bi_init_pipeout(t_mshc *msh, t_cmd *cmd, int *fd1_savep)
{
	if (cmd->iotypes[1] != 1)
		return (0);
	if ((*fd1_savep = dup(1)) < 0)
	{
		msh_err(msh, "Could not save stdout.");
		return (1);
	}
	if (dup2(cmd->rhspfd[1], 1) < 0)
	{
		msh_err(msh, "Could not set pipe out to stdout.");
		return (1);
	}
	return (0);
}

void		msh_bi_disable_pipeout(t_mshc *msh, t_cmd *cmd, int fd1_save)
{
	if (cmd->iotypes[1] != 1 || fd1_save < 0)
		return ;
	if (dup2(fd1_save, 1) < 0)
	{
		msh_err(msh, "Could not restore stdout.");
		exit(1);
	}
	if (close(fd1_save) < 0)
		msh_err(msh, "Could not close stdout dup.");
	return ;
}
