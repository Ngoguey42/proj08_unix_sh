/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:36:54 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/28 10:31:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>

/*
** All shells have a 'PWD' and 'SHLVL' on loading default.
** All shells but csh and tcsh have '_' env variable on loading default.
*/

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
								(ft_strlen(envp[count]) + 1));
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
		(void)msh_new_envvar_m(msh, "SHLVL=1");
	else
	{
		n = ft_atoi(*ptr + ft_strcharlen(*ptr, '=') + 1);
		ft_strcpy(str, "SHLVL=");
		ft_itoa_c(n + 1, str + 6, 10);
		qprintf("DEBUG: %s %d\n", *ptr, n);
		(void)msh_update_envvar_m(msh, str);
	}
	return ;
}

static void	update_pwd(t_msh *msh)
{
	char	str[4 + 1 + PATH_MAX + 1];

	ft_strcpy(str, "PWD=");
	ft_strcat(str, msh->mshpath);
	(void)msh_update_envvar_m(msh, str);
	return ;
}

static void	update__(t_msh *msh)
{
	char	str[1 + 1 + 1];
	char	*str2;

	(void)msh;
	if (msh_get_envvarp(msh, "_") == NULL)
	{
		ft_strcpy(str, "_=");
		str2 = ft_strjoin(str, msh->mshex);
		if (str2 == NULL)
			exit(1);
		(void)msh_new_envvar(msh, str2);
	}
	return ;
}

int			msh_init_msh(t_msh *msh, char *ex)
{
	extern char	**environ;

	ft_bzero(msh, sizeof(msh));
	msh->mshex = ex;
	if ((msh->mshstwd = getcwd(NULL, 0)) == NULL)
		return (1);
	if (msh_resolve_binpath(msh))
		return (1);
	if (dup_environ(&msh->env, environ))
		return (1);
	update_shlvl(msh);
	update_pwd(msh);
	update__(msh);
	ft_memcpy(msh->bi_f, (t_mshbi[])MSHBIN_F, sizeof(msh->bi_f));
	ft_memcpy(msh->bi_n, (char[][MSHBIN_MAXN])MSHBIN_N, sizeof(msh->bi_n));
	return (0);
}
