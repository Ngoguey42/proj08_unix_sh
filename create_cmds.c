/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 08:50:43 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 11:35:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

#define TOKENTYPE ((t_tkn*)(*atknp)->content)->type

static void		move_tokens(t_list *atknp[1], t_cmd *cmd)
{
	t_list	*tmp_tkn;
	int		t;
	
	while (*atknp != NULL && (t = TOKENTYPE) !=
		MTK_END && t != MTK_SEMI && t != MTK_PIPE)
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

static void		get_command(t_msh *msh, t_cmd *cmd)
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
}

static int		new_cmd(t_msh *msh, t_list *atknp[1], t_list *acmd[1])
{
	t_list	*tmp_tkn;
	t_cmd	cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	move_tokens(atknp, &cmd);
	if (TOKENTYPE == MTK_SEMI || TOKENTYPE == MTK_PIPE)
	{
		if (TOKENTYPE == MTK_PIPE)
			cmd.iotypes[1] = 1;
		if ((tmp_tkn = ft_lstpullfirst(atknp)) != NULL)
			ft_lstdelone(&tmp_tkn, &ft_lstfreecont);
		else
			msh_err(msh, "Could not pull token link. 2");
	}
	get_command(msh, &cmd);
	if (cmd.is_builtin == true || cmd.cmdpath != NULL)
		msh_cmd_get_av(msh, &cmd);
	if (ft_lstnewback((t_list**)acmd, (void*)&cmd, sizeof(t_cmd)) == NULL)
        exit(1);
	return (0);
}


void            msh_split_cmd(t_msh *msh, t_list *atknp[1], t_list *acmd[1])
{
	while (*atknp != NULL && TOKENTYPE != MTK_END)
	{
		(void)new_cmd(msh, atknp, acmd);
		
	}
	(void)msh;
	(void)atknp;
	(void)acmd;
	(void)msh;
	
}
