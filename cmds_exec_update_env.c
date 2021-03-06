/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_update_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 07:31:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/22 09:46:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

static void		add_locvars(t_msh *msh, t_cmd *cmd)
{
	t_list	*lst;

	lst = *cmd->alvar;
	while (lst != NULL)
	{
		msh_update_envvar(msh, (char*)lst->content);
		lst = lst->next;
	}
	*cmd->alvar = NULL;
	return ;
}

void			msh_exec_cmd_update_env(t_msh *msh, t_cmd *cmd)
{
	if (cmd->ignore_env == true)
	{
		if (msh->env != NULL)
			msh_free_env(msh);
		msh->env = (char**)malloc(sizeof(char*));
		if (msh->env == NULL)
			msh_errmem(msh);
		*msh->env = NULL;
	}
	add_locvars(msh, cmd);
	return ;
}
