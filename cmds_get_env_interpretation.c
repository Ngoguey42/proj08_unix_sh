/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_env_interpretation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 09:17:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/21 10:01:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <minishell.h>

/*
** Interpretation of env builtin.
*/

/*
** 'store_lvar' stores local variables in 'cmd'.
** *
** 'interpret_binary' updates 'cmd' with binary's data.
** *
** 'msh_cmd_get_env_interpretation' reads env's arguments.
**			t	0	flags
**				1	local variables
**				2	binary found(unused)
*/

static void		store_lvar(t_mshc *msh, t_list *alvar[1], char *arg)
{
	if (ft_lstnewback((t_list**)alvar, (void*)arg, ft_strlen(arg) + 1) == NULL)
		msh_errmem(msh);
	return ;
}

static void		interpret_binary(t_mshc *msh, t_cmd *cmd)
{
	cmd->is_builtin = false;
	cmd->bi_index = 0;
	cmd->binerr = ft_getcmdpath_env(*(cmd->cmdav + cmd->avpad),
					(const char**)msh->env, &cmd->cmdpath);
	if (cmd->binerr == ENOMEM)
		msh_errmem(msh);
	return ;
}

void			msh_cmd_get_env_interpretation(t_mshc *msh, t_cmd *cmd)
{
	char	**av;
	int		t;

	av = cmd->cmdav + 1;
	t = 0;
	while (*av != NULL)
	{
		if (t == 0 && ft_strlen(*av) == ft_strspn(*av, "-i") && (++cmd->avpad))
			cmd->ignore_env = 1;
		else if (t <= 1 && **av != '=' && ft_strchr(*av, '=') && (++cmd->avpad))
		{
			store_lvar(msh, cmd->alvar, *av);
			t = 1;
		}
		else
		{
			cmd->avpad++;
			interpret_binary(msh, cmd);
			break ;
		}
		av++;
	}
	return ;
}
