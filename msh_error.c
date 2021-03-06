/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:46:06 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 11:12:06 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <minishell.h>
#include <stdlib.h>

#define MSH_ERR_FD 2

/*
** 'msh_err' Prints a given error string with ft_printf.
** 'msh_errmem' Handles malloc's fails.
*/

void		msh_err(t_mshc *msh, const char *format, ...)
{
	va_list	ap;

	if (msh != NULL)
		ft_dprintf(MSH_ERR_FD, "%s: ", msh->mshex);
	else
		ft_putstr_fd("msh: ", MSH_ERR_FD);
	va_start(ap, format);
	ft_vdprintf(MSH_ERR_FD, format, ap);
	va_end(ap);
	ft_putchar_fd('\n', MSH_ERR_FD);
	return ;
}

void		msh_errmem(t_mshc *msh)
{
	msh_err(msh, sys_errlist[ENOMEM]);
	exit(1);
}

void		msh_cmd_err(t_mshc *msh, const t_cmd *cmd, int err)
{
	const char	*ptr;
	int			len;

	if (cmd->is_builtin == false && cmd->bi_index == 3)
	{
		ptr = *(cmd->cmdav + cmd->avpad);
		len = ft_strlen(ptr);
	}
	else
	{
		ptr = cmd->cmd_str;
		len = (int)ft_strcspn(cmd->cmd_str, "<>;| \t");
	}
	if (err == -2)
		msh_err(msh, "%! $.*r: %s", len, ptr, "Command not found");
	else
	{
		if (err < 0)
			err = 0;
		msh_err(msh, "%! $.*r: %s", len, ptr, sys_errlist[err]);
	}
	return ;
}
