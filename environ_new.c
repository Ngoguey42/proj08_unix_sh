/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:47:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/22 08:50:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** 'msh_new_envvar_m' Allocates a new variable and adds it to the environment.
** 'msh_update_envvar_m' Updates or allocates a new variable in environment.
*/

char	**msh_new_envvar(t_msh *msh, char *line)
{
	char	**ret;

	ret = ft_envnew(&msh->env, line);
	if (ret == NULL)
		msh_errmem(msh);
	return (ret);
}

char	**msh_update_envvar(t_msh *msh, char *line)
{
	char	**ret;

	ret = ft_envupdate(&msh->env, line);
	if (ret == NULL)
		msh_errmem(msh);
	return (ret);
}

char	**msh_new_envvar_m(t_msh *msh, char *line)
{
	char	**ret;

	ret = ft_envnew_m(&msh->env, line);
	if (ret == NULL)
		msh_errmem(msh);
	return (ret);
}

char	**msh_update_envvar_m(t_msh *msh, char *line)
{
	char	**ret;

	ret = ft_envupdate_m(&msh->env, line);
	if (ret == NULL)
		msh_errmem(msh);
	return (ret);
}
