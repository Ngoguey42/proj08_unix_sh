/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_locvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 10:18:33 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/05 08:49:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_cmd_get_locvar(t_mshc *msh, t_cmd *cmd)
{
	t_tkn	*tkn;
	t_list	*lst;
	t_list	*new;

	lst = *cmd->atkn;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type == MTK_LVAR)
		{
			(void)msh_delin_locvars(tkn->ptr, cmd->alvar);
			new = ft_lstnew(tkn->ptr, tkn->len + 1);
			if (new == NULL)
				msh_errmem(msh);
			((char*)new->content)[tkn->len] = '\0';
			ft_lstpushback(cmd->alvar, new);
		}
		lst = lst->next;
	}
	return ;
}
