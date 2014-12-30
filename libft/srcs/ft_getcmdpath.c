/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcmdpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 10:04:04 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/30 11:17:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <errno.h> //-42
#include <limits.h>

#define ALLOWED_CHARS1 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALLOWED_CHARS2 "abcdefghijklmnopqrstuvwxyz"
#define ALLOWED_CHARS3 "0123456789+-_["

#define ALLOWED_CHARS ALLOWED_CHARS1""ALLOWED_CHARS2""ALLOWED_CHARS3

/*
** 'test_path' tests access for a given path.
**      returns >= 0 if error (errno), -1 otherwise
** *
** 'ex_path2' is a dependancy of 'ex_path', that deals with env's PATH.
** *
** 'ex_path' determines if cmdname is a binary path or command name.
**		0, Found and available.
**		1, Error searching for path.
**		2, Error searching for path/cmdname.
*/

static int	test_path(char *dirpath, char *cmdname)
{
	char	fullpath[PATH_MAX + 1];

	if (ft_strlen(dirpath) + ft_strlen(cmdname) + 1 > PATH_MAX)
		return (2);
	if (*dirpath != '\0')
	{
		ft_strcpy(fullpath, dirpath);
		ft_strcat(fullpath, "/");
	}
	else
		*fullpath = '\0';
	ft_strcat(fullpath, cmdname);
	if (access(fullpath, X_OK) < 0)
		return (1);
	return (0);
}

static int	cmd_as_cmd(char *path, char *buf, char cmdname[PATH_MAX + 1])
{
	char	dirpath[PATH_MAX + 1];
	size_t	n;

	while (*path != '\0')
	{
		n = ft_strcharlen(path, ':');
		n = (n < PATH_MAX) ? n : PATH_MAX;
		ft_strlcpy(dirpath, path, n + 1);
		if (test_path(dirpath, cmdname) == 0)
		{
			*buf = '\0';
			ft_strcpy(buf, dirpath);
			ft_strcat(buf, "/");
			ft_strcat(buf, cmdname);
			return (0);
		}
		path += n;
		path += (*path == ':') ? 1 : 0;
	}
	*buf = '\0';
	return (2);
}

static int	cmd_as_path(char *buf, char cmdname[PATH_MAX + 1])
{
	if (test_path("", cmdname) == 0)
		ft_strlcpy(buf, cmdname, PATH_MAX + 1);
	else
		*buf = '\0';
	return (1);
}

int			ft_getcmdpath(char *cmd, char *envpath, char *buf)
{
	char	cmdname[PATH_MAX + 1];
	size_t	n;

	n = ft_strspn(cmd, ALLOWED_CHARS);
	n = (n < PATH_MAX) ? n : PATH_MAX;
	ft_strlcpy(cmdname, cmd, n + 1);
	if (ft_memchr((void*)cmd, (int)'/', sizeof(char) * n) != NULL)
		return (cmd_as_path(buf, cmdname));
	if (envpath == NULL)
		return (2);
	if (ft_strnequ(envpath, "PATH=", 5))
		envpath += 5;
	return (cmd_as_cmd(envpath, buf, cmdname));
}
