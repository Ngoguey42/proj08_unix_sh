/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_redir_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 12:58:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 10:07:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <minishell.h>

/*
** 'redir_append' Sets up '>>FILE' redirection.
**			'open' => closed here.
**			'dup2' => closed by child.
** *
** 'redir_write_file' Sets up '>&FILE' redirection.
**			'open' => closed here.
**			'dup2' => closed by child.
** *
** 'redir_write_file_all' Sets up '&>FILE' redirection.
**			'open' => closed here.
**			'dup2' => closed by child.
**			'dup2' => closed by child.
** *
** 'redir_write_fd' Sets up '>&fd' redirection.
**			'dup2' => closed by child.
** *
** 'msh_outredirections' Parses t_red's list for the above in redirections.
*/

static int	redir_append(t_mshc *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_WRONLY | O_APPEND | O_CREAT,
		OCREAT_FLAGS)) < 0)
	{
		msh_err(msh, "%d>>%! $r open, failed.", red->lhsfd, red->file);
		return (1);
	}
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			red->lhsfd, red->file, filefd, red->rhsfd, red->lhsfd);
		return (close(filefd), 1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%!s(%d) close, failed.", red->file, filefd);
	return (0);
}

static int	redir_write_file(t_mshc *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_WRONLY | O_CREAT, OCREAT_FLAGS)) < 0)
	{
		msh_err(msh, "%d>%!r open, failed.", red->lhsfd, red->file);
		return (1);
	}	
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			red->lhsfd, red->file, filefd, filefd, red->lhsfd);
		return (close(filefd), 1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
	return (0);
}

static int	redir_write_file_all(t_mshc *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_WRONLY)) < 0)
	{
		msh_err(msh, "&>%!r open, failed.", red->file);
		return (1);
	}
	if (dup2(filefd, 1) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			1, red->file, filefd, filefd, 1);
		return (close(filefd), 1);
	}
	if (dup2(filefd, 2) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			2, red->file, filefd, filefd, 2);
		return (close(filefd), 1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
	return (0);
}

static int	redir_write_fd(t_mshc *msh, t_red *red)
{
	if (dup2(red->rhsfd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>&%d dup2(%d, %d), failed.",
			red->lhsfd, red->rhsfd, red->rhsfd, red->lhsfd);
		return (1);
	}
	return (0);
}

int			msh_outredirections(t_mshc *msh, t_list *lst)
{
	t_red	*red;
	int		ret;

	ret = 0;
	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->type == MTK_WRIT)
		{
			if (red->file != NULL && red->lhsfd == -1)
				ret = redir_write_file_all(msh, red);
			else if (red->file != NULL)
				ret = redir_write_file(msh, red);
			else
				ret = redir_write_fd(msh, red);
		}
		else if (red->type == MTK_APND)
			ret = redir_append(msh, red);
		if (ret)
			return (1);
		lst = lst->next;
	}
	return (0);
}
