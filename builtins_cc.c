/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 08:05:01 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 08:15:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Builtins Command Center.
*/
/*
** 'msh_is_builtin' searches for a builtin from a givent string.
** *
** 'msh_get_builtin_index' retrieves a builtin index from string.
** *
*/

t_bool		msh_is_builtin(const t_msh *msh, const char *cmd, size_t len)
{
	int		i;

	i = -1;
	while (msh->bi_n[++i][0] != '\0')
	{
		if (ft_strnequ(msh->bi_n[i], cmd, len))
			return (true);
	}
	return (false);
}

int			msh_get_builtin_index(const t_msh *msh, const char *cmd, size_t len)
{
	int		i;

	i = -1;
	while (msh->bi_n[++i][0] != '\0')
		if (ft_strnequ(msh->bi_n[i], cmd, len))
			return (i);
	msh_err(msh, "Could not retreive %.*r builtin.", len, cmd);
	return (0);
}
