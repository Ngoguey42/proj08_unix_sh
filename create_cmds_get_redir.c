/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_get_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 15:37:01 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/01 12:49:08 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static void	extract_redir_and_file(t_msh *msh, t_red *ret, t_list **lstp)
{
	
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
		if (tkn->type >= MTK_HERE && tkn->type <= MTK_WRITE)
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
