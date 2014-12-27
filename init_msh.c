/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:36:54 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 16:11:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>

extern char	**environ;

static int	dup_environ(char ***env, char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	if ((*env = (char**)malloc(sizeof(char*) * (count + 1))) == NULL)
		return (1);
	(*env)[count] = NULL;
	qprintf("found %u env lines\n", count); //debug
	while (count-- > 0)
	{
		(*env)[count] = (char*)malloc(sizeof(char) *
								(ft_strlen(envp[count] + 1)));
		if ((*env)[count] == NULL)
			return (1);
		ft_strcpy((*env)[count], envp[count]);
	}
	return (0);
}

static void	update_shlvl(t_msh *msh)
{
	char	**ptr;
	char	str[5 + 1 + 5 + 1];
	int		n;

	ptr = msh_get_envvarp(msh, "SHLVL");
	if (ptr == NULL)
	{
		if (msh_new_envvar(msh, "SHLVL=1") == NULL)
			exit(1);
	}
	else
	{
		n = ft_atoi(*ptr + ft_strcharlen(*ptr, '=') + 1);

		ft_strcpy(str, "SHLVL=");
		ft_itoa_c(n + 1, str + 6,  10);
		qprintf("DEBUG: %s %d\n", *ptr, n);
		msh_update_envvar(msh, str);
	}
}

static int	update_environ(t_msh *msh)
{
	update_shlvl(msh);
	return (0);
	
}

int			msh_init_msh(t_msh *msh, char *ex)
{
	ft_bzero(msh, sizeof(msh));
	msh->mshex = ex;
	if ((msh->mshstwd = getcwd(NULL, 0)) == NULL)
		return (1);
	if (msh_resolve_binpath(msh))
		return (1);
	if (dup_environ(&msh->env, environ) || update_environ(msh))
		return (1);
	return (0);
}
