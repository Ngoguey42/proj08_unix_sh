/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 08:05:01 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/16 12:26:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
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

t_bool		msh_is_builtin(t_mshc *msh, const char *cmd, size_t len)
{
	int		i;
	size_t	len2;

	i = -1;
	while (msh->bi_n[++i][0] != '\0')
	{
		len2 = MAX(ft_strlen(msh->bi_n[i]), len);		
		if (ft_strnequ(msh->bi_n[i], cmd, len2))
			return (true);
	}
	return (false);
}

int			msh_get_builtin_index(t_mshc *msh, const char *cmd, size_t len)
{
	int		i;
	size_t	len2;

	i = -1;
	while (msh->bi_n[++i][0] != '\0')
	{
		len2 = MAX(ft_strlen(msh->bi_n[i]), len);		
		if (ft_strnequ(msh->bi_n[i], cmd, len2))
			return (i);
	}
	msh_err(msh, "Could not retreive %r builtin.", cmd);
	return (0);
}
