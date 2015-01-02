/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_get_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 15:37:01 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/02 11:14:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

static void	extract_redir_and_file(t_msh *msh, t_red *red, t_list **lstp)
{
	t_tkn	*redir;
	t_tkn	*next;

	ft_bzero(red, sizeof(t_red));
	redir = (t_tkn*)(*lstp)->content;
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

void		msh_cmd_get_redir(t_msh *msh, t_cmd *cmd)
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
				exit(1);
		}
		else if (tkn-> type == MTK_FILE)
			msh_err(msh, "Encountered an MTK_FILE without a redirection.");
		lst = lst->next;
	}
	return ;
}
