/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/18 09:04:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <minishell.h>

/*
** 'msh_cmd_get_cmd' Retreives binary path from MTK_CMD token.
*/

void		msh_cmd_get_cmd_old(t_mshc *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_tkn	*tkn;

	lst = cmd->atkn == NULL ? NULL : *cmd->atkn;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type == MTK_CMD)
		{
			cmd->cmd_str = tkn->ptr;
			cmd->is_builtin = msh_is_builtin(msh, tkn->ptr, tkn->len);
			if (cmd->is_builtin == false)
			{
				cmd->binerr = ft_getcmdpath_envl(tkn->ptr,
					(const char**)msh->env, *cmd->alvar, &cmd->cmdpath);
				if (cmd->binerr == ENOMEM)
					msh_errmem(msh);
			}
			else
				cmd->bi_index = msh_get_builtin_index(msh, tkn->ptr, tkn->len);
		}
		lst = lst->next;
	}
}

void		msh_cmd_get_cmd_bones(t_mshc *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_tkn	*tkn;

	lst = cmd->atkn == NULL ? NULL : *cmd->atkn;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type == MTK_CMD)
		{
			cmd->cmd_str = tkn->ptr;
			cmd->is_builtin = msh_is_builtin(msh, tkn->ptr, tkn->len);
			if (cmd->is_builtin)
				cmd->bi_index = msh_get_builtin_index(msh, tkn->ptr, tkn->len);
			break ;
		}
		lst = lst->next;
	}	
	return ;
}

void		msh_cmd_get_cmd(t_mshc *msh, t_cmd *cmd)
{
	if (cmd->is_builtin == false)
	{
		cmd->binerr = ft_getcmdpath_envl(cmd->cmd_str,
			(const char**)msh->env, *cmd->alvar, &cmd->cmdpath);
		if (cmd->binerr == ENOMEM)
			msh_errmem(msh);
	}
	return ;	
}
