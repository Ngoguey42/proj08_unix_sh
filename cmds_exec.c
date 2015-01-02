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

static void	dodup2(int fd, int def_fd)
{
	if (fd == def_fd)
		return ;
	
}

static void	child(t_msh *msh, t_cmd *cmd)
{
	if (cmd->iofds[0] != 0 && dup2(cmd->iofds[0], 0) < 0)
	{
		msh_err(msh, "%s: in dup2 failed.", cmd->cmdpath);
		exit(0);
	}
	if (cmd->iofds[0] != 0)
		close(cmd->iofds[0]);
	if (cmd->iofds[1] != 1 && dup2(cmd->iofds[1], 1) < 0)
	{
		msh_err(msh, "%s: out dup2 failed.", cmd->cmdpath);
		exit(0);
	}
	if (cmd->iofds[0] != 0)
		close(cmd->iofds[0]);

	close(cmd->iofds[0]);
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
