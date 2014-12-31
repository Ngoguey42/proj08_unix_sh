/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 09:57:54 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 10:21:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
