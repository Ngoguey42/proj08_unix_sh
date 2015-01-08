/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:36:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 15:09:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>

/*
** All shells have a 'PWD' and 'SHLVL' on loading default.
*/
/*
** 'dup_environ' Duplicates a givent environment.
** 'update_shlvl' Updates or creates SHLVL variable.
** 'update_pwd' Overwrite PWD variable.
** 'update_path' Adds PATH variable, if missing.
** 'msh_init_msh' Initialized the t_msh instance.
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
		(void)msh_update_envvar_m(msh, str);
	}
	return ;
}

void		msh_update_pwd(t_msh *msh)
{
	char	str[6 + 1 + PATH_MAX + 1];
	char	*cur;

	cur = msh_get_envvar(msh, "PWD");
	ft_strcpy(str, "OLDPWD=");
	if (getcwd(str + 7, PATH_MAX + 1) == NULL)
	{
		msh_err(msh, "Could not collect cwd.");
		exit(1);
	}
	if (cur == NULL)
		(void)msh_update_envvar_m(msh, str + 3);
	else if (!ft_strequ(cur, str + 3))
	{
		(void)msh_update_envvar_m(msh, str + 3);
		(void)msh_update_envvar_m(msh, str);
	}
	return ;
}

static void	update_path(t_msh *msh)
{
	if (msh_get_envvarp(msh, "PATH") == NULL)
		msh_update_envvar_m(msh, DEFAULT_PATH);
	return ;
}

int			msh_init_msh(t_msh *msh, char *ex)
{
	extern char	**environ;

	ft_bzero(msh, sizeof(msh));
	msh->continue_ = 1;
	msh->mshex = ex;
	msh->mshenv = environ;
	msh->stdin_isatty = isatty(0);
	if (dup_environ(&msh->env, environ))
		return (1);
	update_shlvl(msh);
	msh_update_pwd(msh);
	update_path(msh);
	ft_memcpy(msh->bi_f, (void (*[])())MSHBIN_F, sizeof(msh->bi_f));
	ft_memcpy(msh->bi_n, (char[][MSHBIN_MAXN])MSHBIN_N, sizeof(msh->bi_n));
	ft_memcpy(msh->op, (char[][3])MSH_OP, sizeof(msh->op));
	ft_memcpy(msh->red_f, (void (*[])())REDSAVEFUNCS, sizeof(msh->red_f));
	return (0);
}
