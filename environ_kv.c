/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_kv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 09:42:06 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 10:59:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** 'msh_new_envvar_m' Allocates a new variable and adds it to the environment.
** 'msh_update_envvar_m' Updates or allocates a new variable in environment.
*/

char	**msh_new_envkv_m(t_msh *msh, char *k, char *v)
{
	char	**ret;

	ret = ft_envnewkv_m(&msh->env, k, v);
	if (ret == NULL)
		msh_errmem(msh);
	return (ret);
}

char	**msh_update_envkv_m(t_msh *msh, char *k, char *v)
{
	char	**ret;

	ret = ft_envupdatekv_m(&msh->env, k, v);
	if (ret == NULL)
		msh_errmem(msh);
	return (ret);
}

int		msh_del_envk(t_msh *msh, char *k)
{
	return (ft_envdel(msh->env, k));
}
