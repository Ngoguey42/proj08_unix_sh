/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 15:22:44 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 07:26:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

/*
** 'msh_exec_cmd_pipeout' Set up out pipe (right handed side), called by child.
**			'dup2' => closed by child.
** 'msh_exec_cmd_pipein' Set up in pipe (left handed side), called by child.
**			'dup2' => closed by child.
** 'msh_exec_cmd_openpipe' Opens pipe (right handed side), called by msh.
**			'pipe' => closed in 'msh_exec_cmd_closepipeX' and set to -2.
** 'msh_exec_cmd_closepipe' Closes pipe (left handed side), called by msh.
*/

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
	msh_exec_cmd_closepiper(msh, cmd);
/* 	if (close(cmd->rhspfd[0]) < 0) */
/* 		msh_err(msh, "could not close rhs pipe read."); */
/* 	if (close(cmd->rhspfd[1]) < 0) */
/* 		msh_err(msh, "could not close rhs pipe write."); */
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
	msh_exec_cmd_closepipel(msh, cmd);
/* 	if (close(cmd->lhspfd[0])) */
/* 		msh_err(msh, "could not close lhs pipe read."); */
/* 	if (close(cmd->lhspfd[1])) */
/* 		msh_err(msh, "could not close lhs pipe write."); */
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

void		msh_exec_cmd_closepipel(t_msh *msh, t_cmd *cmd)
{
	t_cmd	*lcmd;

	lcmd = cmd->lhspcmd;
	if (lcmd != NULL && lcmd->rhspfd[0] == -2)
		cmd->lhspfd[0] = -2;
	else if (close(cmd->lhspfd[0]) < 0)
		msh_err(msh, "could not close lhs pipe read.");
	else
	{
		cmd->lhspfd[0] = -2;
		if (lcmd != NULL)
			lcmd->rhspfd[0] = -2;
	}
	if (lcmd != NULL && lcmd->rhspfd[1] == -2)
		cmd->lhspfd[1] = -2;
	else if (close(cmd->lhspfd[1]) < 0)
		msh_err(msh, "could not close lhs pipe write.");
	else
	{
		cmd->lhspfd[1] = -2;
		if (lcmd != NULL)
			lcmd->rhspfd[1] = -2;
	}
	return ;
}


void		msh_exec_cmd_closepiper(t_msh *msh, t_cmd *cmd)
{
	t_cmd	*rcmd;

	rcmd = cmd->rhspcmd;
	if (rcmd != NULL && rcmd->lhspfd[0] == -2)
		cmd->rhspfd[0] = -2;
	else if (close(cmd->rhspfd[0]) < 0)
		msh_err(msh, "could not close rhs pipe read.");
	else
	{
		cmd->rhspfd[0] = -2;
		if (rcmd != NULL)
			rcmd->lhspfd[0] = -2;
	}
	if (rcmd != NULL && rcmd->lhspfd[1] == -2)
		cmd->rhspfd[1] = -2;
	else if (close(cmd->rhspfd[1]) < 0)
		msh_err(msh, "could not close rhs pipe write.");
	else
	{
		cmd->rhspfd[1] = -2;
		if (rcmd != NULL)
			rcmd->lhspfd[1] = -2;
	}
	return ;
}
