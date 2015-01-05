/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 08:46:55 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/05 13:24:45 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

#define MSH_ERR_FD 5

void		msh_err(const t_msh *msh, const char *format, ...)
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

void		msh_errmem(const t_msh *msh)
{
	msh_err(msh, "Malloc failed.");
	exit(1);
}
