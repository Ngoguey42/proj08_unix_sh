/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_binpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 16:10:26 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 16:56:29 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

/*
** 'msh_resolve_binpath' looks for an absolute path (beginning with /)
*/

int			msh_resolve_binpath(t_msh *msh)
{
	char	*path;

	if (*msh->mshex == '/')
	{
		if ((path = ft_strdup(msh->mshex)) == NULL)
			return (1);
	}
	else
	{
		if ((path = (char*)malloc(sizeof(char) * (ft_strlen(msh->mshstwd)
						+ ft_strlen(msh->mshex) + 2))) == NULL)
			return (1);
		ft_strcpy(path, msh->mshstwd);
		ft_strcat(path, "/");
		ft_strcat(path, msh->mshex);
	}
	(void)ft_resolve_path(path);
	if (ft_strlen(path) > PATH_MAX)
	{
		ft_dprintf(2, "%s: Binary path too long.\n", msh->mshex);
		return (1);
	}
	ft_strcpy(msh->mshpath, path);
	free(path);
	return (0);
}
