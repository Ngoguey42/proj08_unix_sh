/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_redir_pertype.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/18 08:34:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <minishell.h>

/*
** 'msh_saveredir_here' [digits]<<keyword
** *
** 'msh_saveredir_apnd' [digits]>>file
** *
** 'msh_saveredir_read' [digits]<{&digits|file}
** *
** 'msh_saveredir_write' [digits|&]>{&digits|file}
** *
*/

void		msh_saveredir_here(t_mshc *msh, t_red *red, const t_tkn *t[2],
						const t_cmd *cmd)
{
	red->error |= msh_get_redir_nbr(t[0]->ptr, &red->lhsfd, 0);
	if (t[1]->type != MTK_FILE)
		red->error |= MSH_RMISSING;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)t[1]->ptr, t[1]->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		msh_expand_redir_tilde(msh, red, cmd);
		red->file[t[1]->len] = '\0';
	}
	return ;
}

void		msh_saveredir_apnd(t_mshc *msh, t_red *red, const t_tkn *t[2],
						const t_cmd *cmd)
{
	red->error |= msh_get_redir_nbr(t[0]->ptr, &red->lhsfd, 1);
	if (t[1]->type != MTK_FILE || t[1]->len == 0)
		red->error |= MSH_RMISSING;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)t[1]->ptr, t[1]->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[t[1]->len] = '\0';
		msh_expand_redir_tilde(msh, red, cmd);
		if (red->file_err || (red->file_err = ft_access(red->file, W_OK)) != 0)
			red->error |= MSH_RINVALID;
	}
	return ;
}

void		msh_saveredir_read(t_mshc *msh, t_red *red, const t_tkn *t[2],
						const t_cmd *cmd)
{
	red->error |= msh_get_redir_nbr(t[0]->ptr, &red->lhsfd, 0);
	if (t[1]->type != MTK_FILE)
		red->error |= MSH_RMISSING;
	else if (*t[1]->ptr == '&')
		red->error |= msh_get_redir_nbr(t[1]->ptr + 1, &red->rhsfd, -1) << 3;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)t[1]->ptr, t[1]->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[t[1]->len] = '\0';
		msh_expand_redir_tilde(msh, red, cmd);
		if (red->file_err || (red->file_err = ft_access(red->file, R_OK)) != 0)
			red->error |= MSH_RINVALID;
	}
	return ;
}

void		msh_saveredir_write(t_mshc *msh, t_red *red, const t_tkn *t[2],
						const t_cmd *cmd)
{
	if (*t[0]->ptr == '&')
		red->lhsfd = -1;
	else
		red->error |= msh_get_redir_nbr(t[0]->ptr, &red->lhsfd, 1);
	if (t[1]->type != MTK_FILE)
		red->error |= MSH_RMISSING;
	else if (*t[1]->ptr == '&')
		red->error |= msh_get_redir_nbr(t[1]->ptr + 1, &red->rhsfd, -1) << 3;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)t[1]->ptr, t[1]->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[t[1]->len] = '\0';
		msh_expand_redir_tilde(msh, red, cmd);
		if (red->file_err || (red->file_err = ft_access(red->file, W_OK)) != 0)
			red->error |= MSH_RINVALID;
	}
	return ;
}
