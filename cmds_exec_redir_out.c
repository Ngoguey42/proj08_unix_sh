/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_redir_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 12:58:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 08:03:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <minishell.h>

/*
** 'redir_append' Sets up '>>FILE' redirection.
**			'open' => closed here OR exit OR failed.
**			'dup2' => closed by child.
** *
** 'redir_write_file' Sets up '>&FILE' redirection.
**			'open' => closed here OR exit OR failed.
**			'dup2' => closed by child.
** *
** 'redir_write_file_all' Sets up '&>FILE' redirection.
**			'open' => closed here OR exit OR failed.
**			'dup2' => closed by child.
**			'dup2' => closed by child.
** *
** 'redir_write_fd' Sets up '>&fd' redirection.
**			'dup2' => closed by child.
** *
** 'msh_outredirections' Parses t_red's list for the above in redirections.
*/

static void	redir_append(t_msh *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_APPEND)) < 0)
	{
		msh_err(msh, "%d>>%! $r open, failed.", red->lhsfd, red->file);
		exit(1);
	}
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			red->lhsfd, red->file, filefd, red->rhsfd, red->lhsfd);
		exit(1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%!s(%d) close, failed.", red->file, filefd);
	return ;
}

static void	redir_write_file(t_msh *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_WRONLY)) < 0)
	{
		msh_err(msh, "%d>%!r open, failed.", red->lhsfd, red->file);
		exit(1);
	}
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			red->lhsfd, red->file, filefd, filefd, red->lhsfd);
		exit(1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
	return ;
}

static void	redir_write_file_all(t_msh *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_WRONLY)) < 0)
	{
		msh_err(msh, "&>%!r open, failed.", red->file);
		exit(1);
	}
	if (dup2(filefd, 1) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			1, red->file, filefd, filefd, 1);
		exit(1);
	}
	if (dup2(filefd, 2) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			2, red->file, filefd, filefd, 2);
		exit(1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
	return ;
}

static void	redir_write_fd(t_msh *msh, t_red *red)
{
	if (dup2(red->rhsfd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>&%d dup2(%d, %d), failed.",
			red->lhsfd, red->rhsfd, red->rhsfd, red->lhsfd);
		exit(1);
	}
	return ;
}

void		msh_outredirections(t_msh *msh, t_list *lst)
{
	t_red	*red;

	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->type == MTK_WRIT)
		{
			if (red->file != NULL)
			{
				if (red->lhsfd == -1)
					redir_write_file_all(msh, red);
				else
					redir_write_file(msh, red);
			}
			else
				redir_write_fd(msh, red);
		}
		else if (red->type == MTK_APND)
			redir_append(msh, red);
		lst = lst->next;
	}
	return ;
}
