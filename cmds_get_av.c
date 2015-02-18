/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_av.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:04 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/18 07:38:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <minishell.h>

/*
** 'msh_cmd_get_av' Allocates the table for binaries' argv.
*/

static void	build_string(t_mshc *msh, const t_cmd *cmd,
								char **str, const t_tkn *tkn)
{
	char	*expansion;
	int		ret;

	if ((*str = (char*)ft_memdup(tkn->ptr, 1 + tkn->len)) == NULL)
		msh_errmem(msh);
	(*str)[tkn->len] = '\0';
	ret = ft_expand_tilde_envl(*str, (const char**)msh->env, *cmd->alvar,
								&expansion);
	if (ret == ENOMEM)
		msh_errmem(msh);
	else if (ret >= 0)
	{
		free(*str);
		*str = expansion;
	}
	return ;
}

void		msh_cmd_get_av(t_mshc *msh, t_cmd *cmd)
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
			build_string(msh, cmd, &str, tkn);
			if (ft_tabadd(avargs, str))
				msh_errmem(msh);
		}
		lst = lst->next;
	}
	cmd->cmdav = *(char***)avargs;
	ft_tabdel3(avargs);
	return ;
}
