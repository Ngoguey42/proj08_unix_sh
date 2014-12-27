/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:36:54 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 12:42:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <minishell.h>

int			dup_environ(char ***env)
{
	
	return (0);
}

int			msh_init_msh(t_msh *msh)
{
	ft_bzero(&msh, sizeof(msh));
	if (dup_environ(&msh->env))
		return (1);
	return (0);
}
