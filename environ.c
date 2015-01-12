/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 13:47:43 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/28 08:48:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

/*
** 'msh_get_envvarp' Retreives a pointer to an env variable string.
** 'msh_get_envvar' Retreives an env variable string.
** 'msh_new_envvar_m' Allocates a new variable and adds it to the environment.
** 'msh_update_envvar_m' Updates or allocates a new variable in environment.
*/

char	**msh_get_envvarp(t_mshc *msh, const char *key)
{
	const char	**env = (msh != NULL) ? (const char**)msh->env : NULL;
	size_t		klen;

	if (env == NULL)
		return (NULL);
	if (ft_strchr(key, (int)'='))
		klen = ft_strcharlen(key, '=') + 1;
	else
		klen = ft_strlen(key);
	while (*env != NULL)
	{
		if (ft_strnequ(*env, key, klen))
			return ((char**)env);
		env++;
	}
	return (NULL);
}

char	*msh_get_envvar(t_mshc *msh, const char *key)
{
	char **ret;

	ret = msh_get_envvarp(msh, key);
	return (ret == NULL ? NULL : (char*)*ret);
}

char	**msh_new_envvar(t_msh *msh, char *line)
{
	size_t	count;
	char	**newenv;

	count = 0;
	while (msh->env[count] != NULL)
		count++;
	if ((newenv = (char**)malloc(sizeof(char*) * (count + 2))) == NULL)
		exit(1);
	newenv[count + 1] = NULL;
	newenv[count] = line;
	count = 0;
	while (msh->env[count] != NULL)
	{
		newenv[count] = msh->env[count];
		count++;
	}
	free(msh->env);
	msh->env = newenv;
	return (msh->env + count);
}

char	**msh_new_envvar_m(t_msh *msh, char *line)
{
	char	*str;

	if ((str = ft_strdup(line)) == NULL)
		exit(1);
	return (msh_new_envvar(msh, str));
}

char	**msh_update_envvar_m(t_msh *msh, char *line)
{
	char	**ptr;

	ptr = msh_get_envvarp(msh, line);
	if (ptr == NULL)
		return (msh_new_envvar_m(msh, line));
	free(*ptr);
	*ptr = ft_strdup(line);
	if (*ptr == NULL)
		exit(1);
	return (ptr);
}
