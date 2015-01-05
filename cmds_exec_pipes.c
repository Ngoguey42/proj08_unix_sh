/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 15:22:44 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/05 15:47:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

void		msh_exec_cmd_pipeout(t_msh *msh, t_cmd *cmd)
{
	if (cmd->rhspfd[1] <= 0)
	{
		msh_err(msh, "Invalid pipe-in fd.");
		exit(1);
	}
	if (dup2(cmd->rhspfd[1], 1) < 0)
	{
		msh_err(msh, "pipe-in, dup2 failed.");
		exit(1);
	}
	if (close(cmd->rhspfd[0]))
		msh_err(msh, "could not close rhs pipe read.");
	if (close(cmd->rhspfd[1]))
		msh_err(msh, "could not close rhs pipe write.");
	return ;
}

void		msh_exec_cmd_pipein(t_msh *msh, t_cmd *cmd)
{
	if (cmd->lhspfd[0] <= 0)
	{
		msh_err(msh, "Invalid pipe-in fd.");
		exit(1);
	}
	if (dup2(cmd->lhspfd[0], 0) < 0)
	{
		msh_err(msh, "pipe-in, dup2 failed.");
		exit(1);
	}
	if (close(cmd->lhspfd[0]))
		msh_err(msh, "could not close lhs pipe read.");
	if (close(cmd->lhspfd[1]))
		msh_err(msh, "could not close lhs pipe write.");
	return ;
}

int			msh_exec_cmd_openpipe(t_msh *msh, t_list *lst)
{
	t_cmd	*lhscmd;
	t_cmd	*rhscmd;

	lhscmd = (t_cmd*)lst->content;
	if (lst->next == NULL)
	{
		msh_err(msh, "no left hand command block for pipe.");
		return (1);
	}
	rhscmd = (t_cmd*)lst->next->content;
	if (pipe(lhscmd->rhspfd) < 0)
	{
		msh_err(msh, "failed to create pipe.");
		return (1);
	}
	rhscmd->lhspfd[0] = lhscmd->rhspfd[0];
	rhscmd->lhspfd[1] = lhscmd->rhspfd[1];
	return (0);
}

void		msh_exec_cmd_closepipe(t_msh *msh, t_cmd *cmd)
{
	if (close(cmd->lhspfd[0]))
		msh_err(msh, "could not close lhs pipe read.");
	if (close(cmd->lhspfd[1]))
		msh_err(msh, "could not close lhs pipe write.");
	return ;
}
