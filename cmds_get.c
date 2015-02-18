/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:21:11 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/18 09:01:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define TOKENTYPE ((t_tkn*)(*atknp)->content)->type

/*
** 'move_tokens' Moves all tokens into t_cmd.
** *
** 'new_cmd' Creates a new t_cmd, fills it, and stores it in 'acmd'
**		Step1:		Pull tokens from list
**		Step2:		Get Local Variables
**		Step2b:		Get redirections bones (fill it in step5)
**		Step2t:		Get command bones (fill in step5t)
**		Step3:		Request here-documents
**		Step3b:		Do some magic if step2t matched 'env' builtin.
**		Step4:		(See update_iotypes below)
**	!!!(next steps have been moved right before each t_cmd executions)!!!
**		Step5:		Get redirections details
**		Step5b:		Get argv.
**		Step5t:		Get command binary / builtin
** *
** 'update_iotypes' Creates links between pipe-connected t_cmd.
** *
** 'msh_split_cmd' Fills 'acmd' and empties 'atknp'.
** *
*/

static void		move_tokens(t_list *atknp[1], t_cmd *cmd)
{
	t_list	*tmp_tkn;

	while (*atknp != NULL && !MTK_ISBRK(TOKENTYPE))
	{
		tmp_tkn = ft_lstpullfirst(atknp);
		if (tmp_tkn != NULL)
			(void)ft_lstpushback(cmd->atkn, tmp_tkn);
		else
		{
			msh_err(NULL, "Could not pull token link. 1");
			break ;
		}
	}
}

static int		new_cmd(t_mshc *msh, t_list *atknp[1], t_list *acmd[1])
{
	t_list	*tmp_tkn;
	t_cmd	cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	move_tokens(atknp, &cmd);
	if (MTK_ISBRKO(TOKENTYPE))
	{
		if (TOKENTYPE == MTK_PIPE)
			cmd.iotypes[1] = 1;
		if ((tmp_tkn = ft_lstpullfirst(atknp)) != NULL)
			ft_lstdelone(&tmp_tkn, &ft_lstfreecont);
		else
			msh_err(msh, "Could not pull token link. 2");
	}
	msh_cmd_get_locvar(msh, &cmd);
/* 	msh_cmd_get_cmd(msh, &cmd); */
/* 	msh_cmd_get_redir(msh, &cmd); */
/* 	msh_cmd_get_av(msh, &cmd); */
	msh_cmd_get_redir_bones(msh, &cmd);
	msh_cmd_get_cmd_bones(msh, &cmd);
	msh_cmd_get_heredoc(msh, &cmd);
	if (cmd.is_builtin == true && cmd.bi_index == MSHENVINDEX)
		msh_cmd_get_env_interpretation(msh, &cmd);
	if (ft_lstnewback((t_list**)acmd, (void*)&cmd, sizeof(t_cmd)) == NULL)
		msh_errmem(msh);
	return (0);
}

static void		update_iotypes(t_mshc *msh, t_list *cmd)
{
	t_list	*next;

	while (cmd != NULL)
	{
		next = cmd->next;
		if (next && ((t_cmd*)cmd->content)->iotypes[1] == 1)
		{
			((t_cmd*)next->content)->lhspcmd = (t_cmd*)cmd->content;
			((t_cmd*)cmd->content)->rhspcmd = (t_cmd*)next->content;
			((t_cmd*)next->content)->iotypes[0] = 1;
		}
		cmd = next;
	}
	(void)msh;
}

void			msh_split_cmd(t_mshc *msh, t_list *atknp[1], t_list *acmd[1])
{
	if (atknp == NULL)
		return ;
	while (*atknp != NULL && TOKENTYPE != MTK_END)
		(void)new_cmd(msh, atknp, acmd);
	update_iotypes(msh, *acmd);
	return ;
}
