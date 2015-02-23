/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_redir_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 08:35:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 09:24:37 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <minishell.h>
#include <errno.h>
#include <stdlib.h>

/*
** 'get_nbr' Gets a filedescriptor from a given str 'ptr'.
**		ERRORS Cases:
**		if len >= 10^9
**			error = too long
**		else if isdigit && len > 255
**			error = over limit
**		else if !isdigit && !(*str is operator)
**			error = invalid.
** *
**		VALID Cases:
**		if isdigit && len <= 255
**			fd = atoi(ptr)
**		else if !isdigit && *str == operator (== is lhs)
**			fd = default
*/

int				msh_get_redir_nbr(const char *ptr, int *fdp, int def)
{
	int	error;

	error = 0;
	if (ft_strspn(ptr, "0123456789") > 9)
		error = MSH_LFDTOOLONG;
	else if (ft_isdigit(*ptr))
	{
		*fdp = ft_atoi(ptr);
		if (*fdp > 255)
			error = MSH_LFDOVERLIM;
	}
	else if (*ptr == '<' || *ptr == '>')
		*fdp = def;
	else
		error = MSH_LINVALID;
	return (error);
}

void			msh_expand_redir_tilde(t_mshc *msh, t_red *red, const t_cmd *cmd)
{
	char	*expansion;
	int		ret;

	ret = ft_expand_tilde_envl(red->file, (const char**)msh->env,
								*cmd->alvar, &expansion);
	if (ret == ENOMEM)
		msh_errmem(msh);
	else if (ret >= 0)
	{
		free(red->file);
		red->file = expansion;
		red->file_err = ret;
	}
	return ;
}

static int		test_parent_dir(const char *filepath, int mode)
{
	char	path[PATH_MAX + 1];
	char	*ptr;
	int		err;

	if (!filepath)
	{
		msh_err(NULL, "Null file path where it shouldn't be.");
		return (EFAULT);
	}
	ft_strlcpy(path, filepath, PATH_MAX + 1);
	ptr = ft_strrchr(path, '/');
	if (ptr == NULL)
		ft_strcpy(path, ".");
	else
		*(ptr + 1) = '\0';
	err = ft_access(path, mode);
	if ((mode & X_OK) && err == EISDIR)
		return (0);
	return (err);
}

int			msh_get_redirout_perm(t_mshc *msh, const t_red *red)
{
	int		err;

	if ((err = test_parent_dir(red->file, X_OK)) != 0)
		return (err);
	if ((err = ft_access(red->file, 0)) != 0)
	{
		if (err == ENOENT)
			return (test_parent_dir(red->file, W_OK));
		return (err);
	}
	(void)msh;
	return (ft_access(red->file, W_OK));
}
