/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_binpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 16:10:26 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 16:13:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_resolve_path(char *buf)
{
	
	
}




int			msh_resolve_binpath(t_msh *msh)
{
	char	*path;
	qprintf("%s\n", msh->mshex);
	qprintf("%s\n", msh->mshstwd);


	if (*msh->mshex == '/')
	{
		if ((path = ft_strdup(msh->mshex)) == NULL)
			exit(1);
		while (ft_resolve_path(path) != 0)
			;
		if (ft_strlen(path) > PATH_MAX)
			exit(1);
		ft_strcpy(msh->mshpath, msh->mshex);
	}
	else
	{
		if ((path = (char*)malloc(sizeof(char) * (ft_strlen(msh->mshstwd)
						+ ft_strlen(msh->mshex) + 2))) == NULL)
			exit(1);
		ft_strcpy(path, msh->mshstwd);
		ft_strcat(path, "/");
		ft_strcat(path, msh->mshex);
	}
	tmp = msh->mshex + ft_strspn(msh->mshex, "./");

	exit(0); //debug
	free(path);
	return (0);
	
}
