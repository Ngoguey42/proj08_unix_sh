/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_get_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 15:35:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/01 12:35:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** 'msh_cmd_get_cmd' Retreives binary path from MTK_CMD token.
*/

void		msh_cmd_get_cmd(t_msh *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_tkn	*tkn;

	lst = cmd->atkn == NULL ? NULL : *cmd->atkn;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type == MTK_CMD)
		{
			cmd->is_builtin = msh_is_builtin(msh, tkn->ptr, tkn->len);
			if (cmd->is_builtin == false)
				cmd->binerr = ft_getcmdpath(tkn->ptr,
					msh_get_envvar(msh, "PATH"), &cmd->cmdpath);
			else
				cmd->bi_index = msh_get_builtin_index(msh, tkn->ptr, tkn->len);
		}
		lst = lst->next;
	}
	if (cmd->is_builtin == false && cmd->cmdpath == NULL)
		cmd->error |= 0x1;
}
