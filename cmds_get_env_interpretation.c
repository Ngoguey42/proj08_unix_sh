/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_env_interpretation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 09:17:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/05 08:59:07 by ngoguey          ###   ########.fr       */
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

static void		add_env_locvars(t_list *alvar[1], t_list *alvartmp[1])
{
	while (*alvartmp != NULL)
		ft_lstpushback((t_list**)alvar, ft_lstpullfirst((t_list**)alvartmp));
	return ;
}

static void		store_lvar
		(t_mshc *msh, t_list *alvar[1], char *arg, t_list *alvar2[1])
{
	(void)msh_delin_locvars(arg, alvar);
	(void)msh_delin_locvars(arg, alvar2);
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
	if (cmd->ignore_env)
		ft_lstdel((t_list**)cmd->alvar, &ft_lstfreecont);
	return ;
}

void			msh_cmd_get_env_interpretation(t_mshc *msh, t_cmd *cmd)
{
	char	**av;
	int		t;
	t_list	*alvartmp[1];

	av = cmd->cmdav + 1;
	t = 0;
	*alvartmp = NULL;
	while (*av != NULL)
	{
		if (t == 0 && ft_strlen(*av) == ft_strspn(*av, "-i") && (++cmd->avpad))
			cmd->ignore_env = 1;
		else if (t <= 1 && **av != '=' && ft_strchr(*av, '=') &&
				(++cmd->avpad) && (t = 1))
			store_lvar(msh, alvartmp, *av, cmd->alvar);
		else
		{
			cmd->avpad++;
			interpret_binary(msh, cmd);
			break ;
		}
		av++;
	}
	add_env_locvars(cmd->alvar, alvartmp);
	return ;
}
