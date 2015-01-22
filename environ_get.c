/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:47:43 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/22 08:47:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** 'msh_get_envvarp' Retreives a pointer to an env variable string.
** 'msh_get_envvar' Retreives an env variable string.
*/

char	**msh_get_envvarp(t_mshc *msh, const char *key)
{
	return (ft_envgetp((const char**)msh->env, key));
}

char	*msh_get_envvar(t_mshc *msh, const char *key)
{
	return (ft_envget((const char**)msh->env, key));
}
