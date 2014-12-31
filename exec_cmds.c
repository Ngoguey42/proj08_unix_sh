/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 15:36:13 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 15:36:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_exec_cmds(t_msh *msh, t_list *lst)
{
	t_cmd		*cmd;

	while (lst != NULL)
	{
		cmd = (t_cmd*)lst->content;
		if (cmd->is_builtin == true)
			msh->bi_f[cmd->bi_index](msh, cmd);
		else if (cmd->cmdpath != NULL)
			(void)1;
		lst = lst->next;
	}
	
	return ;
}
