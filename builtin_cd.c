/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 10:39:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 13:06:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <minishell.h>

static void	home_dir(t_msh *msh, char *ptr)
{
	int		err;

	if (ptr == NULL)
		msh_err(msh, "cd: HOME not set");
	else
	{
		err = ft_access(ptr + 5, X_OK);
		err = (err == EISDIR) ? 0 : err;
		if (err != 0)
		{
			msh_err(msh, "% !$r: %s", ptr + 5, sys_errlist[err > 0 ? err : 0]);
			return ;
		}
		err = chdir(ptr + 5);
		if (err != 0)
			msh_err(msh, "cd: %s", "chdir failed.");
	}
	return ;
}

static void oldpwd_dir(t_msh *msh, char *ptr)
{
	int		err;

	if (ptr == NULL)
		msh_err(msh, "cd: OLDPWD not set");
	else
	{
		err = ft_access(ptr + 7, X_OK);
		err = (err == EISDIR) ? 0 : err;
		if (err != 0)
		{
			msh_err(msh, "% !$r: %s", ptr + 7, sys_errlist[err > 0 ? err : 0]);
			return ;
		}
		err = chdir(ptr + 7);
		if (err != 0)
			msh_err(msh, "cd: %s", "chdir failed.");
		else
			ft_printf("% !$r\n", ptr + 7);
	}
	return ;
}

static void	regular(t_msh *msh, t_cmd *cmd)
{
	char	*ptr;
	int		err;

	ptr = cmd->cmdav[1];
	err = ft_access(ptr, X_OK);
	err = (err == EISDIR) ? 0 : err;
	if (err != 0)
	{
		msh_err(msh, "% !$r: %s", ptr, sys_errlist[err > 0 ? err : 0]);
		return ;
	}
	err = chdir(ptr);
	if (err != 0)
		msh_err(msh, "cd: %s", "chdir failed.");
	return ;
}

static void	changedir(t_msh *msh, t_cmd *cmd)
{
	if (cmd->cmdav[1] == NULL)
	{
		if (cmd->ignore_env)
			home_dir(msh, NULL);
		else
			home_dir(msh, msh_get_envvar_l(msh, *cmd->alvar, "HOME"));
	}
	else if (ft_strequ(cmd->cmdav[1], "-"))
	{
		if (cmd->ignore_env)
			oldpwd_dir(msh, NULL);
		else
			oldpwd_dir(msh, msh_get_envvar_l(msh, *cmd->alvar, "OLDPWD"));
	}
	else
		regular(msh, cmd);
	msh_update_pwd(msh);
	return ;
}

void		msh_builtin_cd(t_msh *msh, t_cmd *cmd)
{
	int	fd_saves[2];

	if (msh_builtin_init_fds(msh, cmd, fd_saves))
		return ;
	changedir(msh, cmd);
	msh_builtin_disable_fds(msh, cmd, fd_saves);
	return ;
}
