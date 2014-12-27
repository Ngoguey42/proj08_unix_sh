/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 14:25:00 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 14:28:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_print_env(const t_msh *msh)
{
	const char	**env = (msh != NULL) ? (const char**)msh->env : NULL;

	if (env == NULL)
		return ;
	while (*env != NULL)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return ;
}
