/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:40 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/16 14:52:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <minishell.h>

/*
** 'msh_expand_redir_tilde' Tries to expand tilde.
** 'extract_redir_and_file' Exctrats infos, and calls the right function.
** 'msh_cmd_get_redir' Creates t_red from t_tkn tokens.
*/

void		msh_expand_redir_tilde(t_mshc *msh, t_red *red)
{
	char	*expansion;
	int		ret;

	ret = ft_expand_tilde_env(red->file, (const char**)msh->env, &expansion);
	if (ret == ENOMEM)
		msh_errmem(msh);
	else if (ret >= 0)
	{
		free(red->file);
		red->file = expansion;
		red->file_err = ret;
	}
	return ;
}

static void	extract_redir_and_file(t_mshc *msh, t_red *red, t_list **lstp)
{
	t_tkn	*redir;
	t_tkn	*next;

	ft_bzero(red, sizeof(t_red));
	redir = (t_tkn*)(*lstp)->content;
	if ((*lstp)->next == NULL)
	{
		red->error |= MSH_RINVALID;
		return ;
	}
	next = (t_tkn*)(*lstp)->next->content;
	red->type = redir->type;
	msh->red_f[redir->type - 1](msh, red, redir, next);
	red->ptr[0] = redir->ptr;
	red->len[0] = redir->len;
	if (next->type == MTK_FILE)
	{
		*lstp = (*lstp)->next;
		red->ptr[1] = next->ptr;
		red->len[1] = next->len;
	}
	return ;
}

void		msh_cmd_get_redir(t_mshc *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_tkn	*tkn;
	t_red	red;

	lst = cmd->atkn == NULL ? NULL : *cmd->atkn;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type >= MTK_HERE && tkn->type <= MTK_WRIT)
		{
			extract_redir_and_file(msh, &red, &lst);
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
