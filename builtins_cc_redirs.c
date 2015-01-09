/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cc_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 08:15:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/09 14:30:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

/*
** Builtins Command Center, redirections.
*/
/*
** 'save_prev_fd' Duplicates every left handed fds to restore them later.
** *
** 'msh_bi_init_redirs' Initiates redirections for builtins.
** *
** 'msh_bi_disable_redirs' Disables redirections for builtins.
*/

static int	save_prev_fd(t_msh *msh, t_list *lst)
{
	t_red	*red;

	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if ((red->prev_cp = dup(red->lhsfd)) < 0)
		{
			msh_err(msh, "Could not save fd %d.", red->lhsfd);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int			msh_bi_init_redirs(t_msh *msh, t_list *lst)
{
	if (lst == NULL)
		return (0);
	if (save_prev_fd(msh, lst))
		return (1);
	if (msh_inredirections(msh, lst) || msh_outredirections(msh, lst))
		return (1);
	return (0);
}

void		msh_bi_disable_redirs(t_msh *msh, t_list *lst)
{
	t_red	*red;

	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->prev_cp > 0)
		{
			if (dup2(red->prev_cp, red->lhsfd) < 0)
			{
				msh_err(msh, "Could not restore fd %d.", red->lhsfd);
				exit(1);
			}
			if (close(red->prev_cp) < 0)
				msh_err(msh, "Could not close fd %d.", red->prev_cp);
		}
		lst = lst->next;
	}
	return ;
}
