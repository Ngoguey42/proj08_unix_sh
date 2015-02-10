/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_errprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 15:38:11 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/10 07:36:15 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <minishell.h>

/*
** -
*/

static void	print_red_error(t_mshc *msh, const t_red *red)
{
	if (red->error & MSH_LFDTOOLONG)
		msh_err(msh, "file descriptor out of range: %s", sys_errlist[EBADF]);
	else if (red->error & MSH_LFDOVERLIM)
		msh_err(msh, "%u: %s", red->lhsfd, sys_errlist[EBADF]);
	else if (red->error & MSH_RFDTOOLONG)
		msh_err(msh, "file descriptor out of range: %s", sys_errlist[EBADF]);
	else if (red->error & MSH_RFDOVERLIM)
		msh_err(msh, "%u: %s", red->rhsfd, sys_errlist[EBADF]);
	else if (red->file_err != 0)
	{
		if (red->file_err > 0)
			msh_err(msh, "%! $r: %s", red->file, sys_errlist[red->file_err]);
		else
			msh_err(msh, "%! $r: %s", red->file, sys_errlist[0]);
	}
	else if (red->file_err & ~MSH_RMISSING)
		msh_err(msh, "Redirection: %s", sys_errlist[0]);
	return ;
}

static int	red_error(t_mshc *msh, const t_list *lst)
{
	const t_red	*red;

	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->error != 0)
		{
			print_red_error(msh, red);
			return (1);
		}
		lst = lst->next;
	}
	(void)msh;
	return (0);
}

int			msh_cmd_error(t_mshc *msh, const t_cmd *cmd)
{
	if (cmd->ared != NULL)
		if (red_error(msh, *cmd->ared))
			return (1);
	if (cmd->binerr != 0)
	{
		msh_cmd_err(msh, cmd, cmd->binerr);
		return (1);
	}
	return (0);
}
