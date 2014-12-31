/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 10:24:35 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 10:30:09 by ngoguey          ###   ########.fr       */
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
