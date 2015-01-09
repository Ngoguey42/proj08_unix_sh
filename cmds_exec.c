/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 15:09:35 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/09 12:26:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <minishell.h>

/*
** 'child'		Sets pipes, sets redirections, calls binary. Never returns.
** *
** 'waid_all'	Waits for all processes comunicating with pipe.
** *
** 'exec_cmd'	Calls a builtin or 'fork' for a binary.
** 				----If binary
** 				------'fork'
** 				--------Child: Calls 'child' a non-returning function.
** 				-------OR--
** 				--------MSH: If (left handed pipe): closes it for MSH.
** 				-------------If (';' or 'end' following): Waits for all cpid
** 				----------------							(right to left).
** 'msh_exec_cmd' Opens a following pipe and calls 'exec_cmd'.
** *
*/

static void	child(t_msh *msh, t_cmd *cmd)
{
	if (cmd->iotypes[0] == 1)
		msh_exec_cmd_pipein(msh, cmd);
	if (cmd->iotypes[1] == 1)
		msh_exec_cmd_pipeout(msh, cmd);
	if (cmd->ared != NULL)
	{
		if (msh_inredirections(msh, *cmd->ared))
			exit(1);
		if (msh_outredirections(msh, *cmd->ared))
			exit(1);
	}
	execve(cmd->cmdpath, cmd->cmdav, msh->env);
	msh_err(msh, "%s: execve failed.", cmd->cmdpath);
	exit(1);
}

static void	waid_all(t_msh *msh, t_cmd *cmd)
{
	int		printed;

	printed = 0;
	(void)waitpid(cmd->pid, &cmd->wstatus, 0);
	printed = msh_handle_signal(msh, cmd);
	cmd = cmd->lhspcmd;
	while (cmd && cmd->iotypes[1] == 1)
	{
		(void)waitpid(cmd->pid, &cmd->wstatus, 0);
		if (!printed)
			printed = msh_handle_signal(msh, cmd);
		cmd = cmd->lhspcmd;
	}
	(void)msh;
	return ;
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
			msh_exec_cmd_closepipel(msh, cmd);
		if (cmd->iotypes[1] == 0)
		{
			waid_all(msh, cmd);
		}
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
	return (exec_cmd(msh, cmd));
}
