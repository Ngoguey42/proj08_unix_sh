/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 14:34:24 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 14:38:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_ps1(t_mshc *msh)
{
	char	*ps1;

	if (msh->stdin_isatty)
	{
		if ((ps1 = msh_get_envvar(msh, "PS1")) != NULL)
			ft_putstr(ps1 + 4);
		else
			ft_putstr(MSH_PS1);
	}
	return ;
}

void		msh_ps2(t_mshc *msh, const char *d)
{
	char	*ps2;

	if (msh->stdin_isatty)
	{
		if ((ps2 = msh_get_envvar(msh, "PS2")) != NULL)
			ft_putstr(ps2 + 4);
		else if (d != NULL)
			ft_putstr(d);
		else
			ft_putstr(MSH_PS2);
	}
	return ;
}
