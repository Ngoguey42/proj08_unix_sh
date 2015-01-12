/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 13:47:43 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/28 08:48:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** 'msh_get_envvarp' Retreives a pointer to an env variable string.
** 'msh_get_envvar' Retreives an env variable string.
** 'msh_new_envvar_m' Allocates a new variable and adds it to the environment.
** 'msh_update_envvar_m' Updates or allocates a new variable in environment.
*/

char	**msh_get_envvarp(t_mshc *msh, const char *key)
{
	return (ft_envgetp((const char**)msh->env, key));
}

char	*msh_get_envvar(t_mshc *msh, const char *key)
{
	return (ft_envget((const char**)msh->env, key));
}

char	**msh_new_envvar(t_msh *msh, char *line)
{
	char	**ret;

	ret = ft_envnew(&msh->env, line);
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