/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_update_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 07:31:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/22 08:54:57 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

static void		add_locvars(t_msh *msh, t_list *lst)
{
	while (lst != NULL)
	{
		msh_update_envvar(msh, (char*)lst->content);
		lst = lst->next;
	}
	return ;
}

void			msh_exec_cmd_update_env(t_msh *msh, const t_cmd *cmd)
{
	if (cmd->ignore_env == true)
	{
		msh_free_env(msh);
		msh->env = (char**)malloc(sizeof(char*));
		if (msh->env == NULL)
			msh_errmem(msh);
		*msh->env = NULL;
	}
	if (cmd->alvar != NULL)
		add_locvars(msh, *cmd->alvar);
	return ;
}
