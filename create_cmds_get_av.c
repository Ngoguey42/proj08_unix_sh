/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_get_av.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 10:45:36 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 11:00:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>





void	msh_cmd_get_av(t_msh *msh, t_cmd *cmd)
{
	void	**avargs[1];
	t_tkn	*tkn;
	char	*str;

	*(char***)avargs = NULL;
	while (lst != NULL)
	{
		tkn = (t_tkn*)lst->content;
		if (tkn->type == MTK_WORD)
		{
			str = (char*)malloc(sizeof(char) * (1 + tkn->len));
			if (str == NULL)
			{
				msh_err(msh, "Malloc failed.");
				exit(1);
			}
			ft_strncpy(str, tkn->ptr, tkn->len);
			str[tkn->len] = '\0';
			if (ft_tabadd(avargs, lst->ptr, lst->len + 1))
			{
				msh_err(msh, "Malloc failed, ft_tab side.");
				exit(1);
			}
		}
		lst = lst->next;
	}
	cmd->cmdav = *(char***)avargs;
	ft_tabdel(avargs);
	return ;
}
