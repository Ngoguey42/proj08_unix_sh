/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 14:25:00 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 10:32:01 by ngoguey          ###   ########.fr       */
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

void	msh_builtin_env(t_msh *msh, t_cmd *cmd)
{
	(void)cmd;
	msh_print_env(msh);
	return ;
	
}
