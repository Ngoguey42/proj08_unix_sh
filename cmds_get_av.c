/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_get_av.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 10:45:36 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 13:33:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

/*
** 'msh_cmd_get_av' Allocates the table for binaries' argv.
*/

void		msh_cmd_get_av(t_msh *msh, t_cmd *cmd)
{
	void	**avargs[1];
	t_tkn	*tkn;
	char	*str;
	t_list	*lst;

	lst = cmd->atkn == NULL ? NULL : *cmd->atkn;
	*(char***)avargs = NULL;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type == MTK_WORD || tkn->type == MTK_CMD)
		{
			if ((str = (char*)ft_memdup(tkn->ptr, 1 + tkn->len)) == NULL)
				msh_errmem(msh);
			str[tkn->len] = '\0';
			if (ft_tabadd(avargs, str))
				msh_errmem(msh);
		}
		lst = lst->next;
	}
	cmd->cmdav = *(char***)avargs;
	ft_tabdel3(avargs);
	return ;
}
