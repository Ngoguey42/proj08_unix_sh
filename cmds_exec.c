/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 17:10:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/02 18:30:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <minishell.h>
// #include <fcntl.h>

static void	child(t_msh *msh, t_cmd *cmd)
{
	if (cmd->ared != NULL)
	{
		msh_inredirections(msh, *cmd->ared);
	}
	execve(cmd->cmdpath, cmd->cmdav, msh->env);
	msh_err(msh, "%s: execve failed.", cmd->cmdpath);
	exit(1);
}

int			msh_exec_cmd(t_msh *msh, t_cmd *cmd)
{
	int		cpid;

	if (cmd->is_builtin == true)
		msh->bi_f[cmd->bi_index](msh, cmd);
	else if (cmd->cmdpath != NULL)
	{
		if ((cpid = fork()) < 0)
		{
			msh_err(msh, "Fork failed.");
			return (1);
		}
		if (cpid == 0)
			child(msh, cmd);
		(void)wait(NULL);
	}
	return (0);
}
