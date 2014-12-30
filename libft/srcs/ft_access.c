/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 13:41:31 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/30 15:09:15 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libft"

/*
** 'ft_access' in case 'errno' is not allowed.
**		>0	Errno equivalent.
**		0	No error encountered.
**		-1	Undefined error.	
** *
** EFAULT		'pathname' pointer incorrect.
** EINVAL		'mode' incorrect.
** ENAMETOOLONG	'pathname' too long.
** ELOOP		
** ENOTDIR		
** ENOENT		
** EACCES		
** ENOMEM		'malloc' returns NULL.
** EIO			
** EROFS		
** ETXTBSY		
*/

#define FULL_MASK (R_OK & W_OK & X_OK)


int		is_path_valid(char *path, int mode)
{	
	qprintf("Testing %s\n", path);
	if (access(path, mode) == 0)
		return (1);


	
}


int		explore_path(char *path, int mode)
{
	char	pathchunk[PATH_MAX + 1];

	if (*path == '/' )
	{
		ft_strcpy(pathchunk, "/");
		path++;
	}
	else
		ft_strcpy(pathchunk, ".");
	if (!test_path(path, mode))
		
}

int		ft_access(const char *pathname, int mode)
{
	char		path[PATH_MAX + 1];
	int			i;
/* 	const int	rights[][2] = {{R_OK, S_IRUSR}, {W_OK, S_IWUSR}, */

/* 	{X_OK, S_IXUSR}, {R_OK & W_OK, S_IRUSR & S_IWUSR}, */
/* 	{R_OK & X_OK, S_IRUSR & S_IXUSR}, {W_OK & X_OK, S_IWUSR & S_IXUSR}, */
/* 	{R_OK & W_OK & X_OK, S_IRUSR & S_IWUSR & S_IXUSR}, {0, 0}}; */
	if (pathname == NULL)
		return (EFAULT);
	if (mode == 0 || (mode & FULL_MASK != FULL_MASK))
		return (EINVAL);
	if (ft_strlen(pathname) > PATH_MAX)
		return (ENAMETOOLONG);
	*path = '\0';
	(void)ft_resolve_path(ft_resolve_path(ft_strcpy(path, pathname)));
	i = -1;
/* 	while (rights[i] != mode && rights[i] != 0) */
/* 		i++; */
/* 	mode = rights[i]; */
	return (explore_path(path, mode));
}
