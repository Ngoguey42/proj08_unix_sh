/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 08:46:55 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/30 09:00:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_err(t_msh *msh, const char *format, ...)
{
	va_list	ap;

	if (msh != NULL)
		ft_dprintf(2, "%s: ", msh->mshex);
	else
		ft_putstr_fd("msh: ", 2);
	va_start(ap, format);
	ft_vdprintf(2, format, ap);
	va_end(ap);
	ft_putchar_fd('\n', 2);
	return ;
}
