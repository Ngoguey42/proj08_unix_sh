/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:47:43 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/10 07:37:44 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>
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

char	*msh_get_envvar_l(t_mshc *msh, const t_list *lvars, const char *kv)
{
	size_t	len;

	len = ft_strcspn(kv, "=");
	while (lvars != NULL)
	{
		if (ft_strnequ(kv, (char*)lvars->content,
				MAX(len, ft_strcspn((char*)lvars->content, "="))))
			return ((char*)lvars->content);
		lvars = lvars->next;
	}
	return (ft_envget((const char**)msh->env, kv));
}

int		msh_isin_locvars(const char *kv, const t_list *lvars)
{
	size_t	len;

	len = ft_strcspn(kv, "=");
	while (lvars != NULL)
	{
		if (ft_strnequ(kv, (char*)lvars->content,
				MAX(len, ft_strcspn((char*)lvars->content, "="))))
			return (1);
		lvars = lvars->next;
	}
	return (0);
}

int		msh_delin_locvars(const char *kv, t_list *alvar[1])
{
	size_t	len;
	t_list	*lvars;

	lvars = *alvar;
	len = ft_strcspn(kv, "=");
	while (lvars != NULL)
	{
		if (ft_strnequ(kv, (char*)lvars->content,
				MAX(len, ft_strcspn((char*)lvars->content, "="))))
		{
			(void)ft_lstdelcur(alvar, lvars, &ft_lstfreecont);
			return (1);
		}
		lvars = lvars->next;
	}
	return (0);
}
