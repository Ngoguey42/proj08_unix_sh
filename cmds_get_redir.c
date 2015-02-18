/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:40 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/18 09:06:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <errno.h> */
/* #include <stdlib.h> */
#include <minishell.h>

/*
** 'extract_redir_and_file' Exctrats infos, and calls the right function.
** 'msh_cmd_get_redir' Creates t_red from t_tkn tokens.
*/

static void	extract_redir_and_file(t_red *red, t_list **lstp)
{
	t_tkn	*redir;
	t_tkn	*next;

	ft_bzero(red, sizeof(t_red));
	redir = (t_tkn*)(*lstp)->content;
	if ((*lstp)->next == NULL)
	{
		red->error |= MSH_RMISSING;
		return ;
	}
	next = (t_tkn*)(*lstp)->next->content;
	red->type = redir->type;
	red->ptr[0] = redir->ptr;
	red->len[0] = redir->len;
	red->tkn[0] = redir;
	if (next->type == MTK_FILE)
	{
		*lstp = (*lstp)->next;
		red->ptr[1] = next->ptr;
		red->len[1] = next->len;
		red->tkn[1] = next;
	}
	return ;
}

void		msh_cmd_get_redir_bones(t_mshc *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_tkn	*tkn;
	t_red	red;

	lst = cmd->atkn == NULL ? NULL : *cmd->atkn;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (MTK_ISRED(tkn->type))
		{
			extract_redir_and_file(&red, &lst);
			if (ft_lstnewback((t_list**)cmd->ared, (void*)&red,
								sizeof(t_red)) == NULL)
				msh_errmem(msh);
		}
		else if (tkn->type == MTK_FILE)
			msh_err(msh, "Encountered an MTK_FILE without a redirection.");
		lst = lst->next;
	}
	return ;
}

void		msh_cmd_get_redir(t_mshc *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_red	*red;

	lst = cmd->ared == NULL ? NULL : *cmd->ared;
	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		msh->red_f[red->type - 1]
				(msh, red, (const t_tkn*[2]){red->tkn[0], red->tkn[1]}, cmd);
		lst = lst->next;
	}
	return ;
}
