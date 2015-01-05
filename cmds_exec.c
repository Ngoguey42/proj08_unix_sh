/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 15:09:35 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/05 15:51:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <minishell.h>

static void	child(t_msh *msh, t_cmd *cmd)
{
	if (cmd->iotypes[0] == 1)
		msh_exec_cmd_pipein(msh, cmd);
	if (cmd->ared != NULL)
	{
		msh_inredirections(msh, *cmd->ared);
		msh_outredirections(msh, *cmd->ared);
	}
	if (cmd->iotypes[1] == 1)
		msh_exec_cmd_pipeout(msh, cmd);
	execve(cmd->cmdpath, cmd->cmdav, msh->env);
	msh_err(msh, "%s: execve failed.", cmd->cmdpath);
	exit(1);
}

static int	exec_cmd(t_msh *msh, t_cmd *cmd)
{
	if (cmd->is_builtin == true)
		msh->bi_f[cmd->bi_index](msh, cmd);
	else if (cmd->cmdpath != NULL)
	{
		if ((cmd->pid = fork()) < 0)
		{
			msh_err(msh, "Fork failed.");
			return (1);
		}
		if (cmd->pid == 0)
			child(msh, cmd);
		if (cmd->iotypes[0] == 1)
			msh_exec_cmd_closepipe(msh, cmd);
		if (cmd->iotypes[1] == 0)
			(void)waitpid(cmd->pid, NULL, 0);
	}
	return (0);
}

int			msh_exec_cmd(t_msh *msh, t_list *lst)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)lst->content;
	if (cmd->iotypes[1] == 1)
		if (msh_exec_cmd_openpipe(msh, lst))
			return (1);
	if (exec_cmd(msh, cmd))
		return (1);
	return (0);
}
