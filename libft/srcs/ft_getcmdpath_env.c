/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcmdpath_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 08:23:44 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/18 07:57:53 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_getcmdpath_env(const char *cmd, const char **env, char **ptr)
{
	char	*ref[4];

	ref[0] = ft_envget(env, "PATH=");
	ref[1] = ft_envget(env, "HOME=");
	ref[2] = ft_envget(env, "PWD=");
	ref[3] = ft_envget(env, "OLDPWD=");
	if (ref[0] != NULL)
		ref[0] += 5;
	if (ref[1] != NULL)
		ref[1] += 5;
	if (ref[2] != NULL)
		ref[2] += 4;
	if (ref[3] != NULL)
		ref[3] += 7;
	return (ft_getcmdpath(cmd, ref, ptr));
}

int			ft_getcmdpath_envl(const char *cmd, const char **env,
									const t_list *lst, char **ptr)
{
	char	*ref[4];

	ref[0] = ft_envgetl(env, lst, "PATH=");
	ref[1] = ft_envgetl(env, lst, "HOME=");
	ref[2] = ft_envgetl(env, lst, "PWD=");
	ref[3] = ft_envgetl(env, lst, "OLDPWD=");
	if (ref[0] != NULL)
		ref[0] += 5;
	if (ref[1] != NULL)
		ref[1] += 5;
	if (ref[2] != NULL)
		ref[2] += 4;
	if (ref[3] != NULL)
		ref[3] += 7;
	return (ft_getcmdpath(cmd, ref, ptr));
}
