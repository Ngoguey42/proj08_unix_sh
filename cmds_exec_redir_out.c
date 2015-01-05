/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_redir_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 12:58:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/05 13:42:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <minishell.h>

int gi = 0;

static void	redir_append(t_msh *msh,t_red *red)
{
	int		filefd;

	msh_err(msh, "Redir(%d): %d>>%! $r.", ++gi, red->lhsfd, red->file);
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
	{
		msh_err(msh, "%!s(%d) close, failed.", red->file, filefd);
		exit(1);
	}
	return ;
}

static void	redir_write_file(t_msh *msh, t_red *red, int lhsfd)
{
	int		filefd;

	msh_err(msh, "Redir(%d): %d>%! $r.", ++gi, lhsfd, red->file);
	if ((filefd = open(red->file, O_WRONLY)) < 0)
	{
		msh_err(msh, "%d>%!r open, failed.", lhsfd, red->file);
		exit(1);
	}
	msh_err(msh, "fd(%d) = open(%! $r)", filefd , red->file);
	if (dup2(filefd, lhsfd) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			lhsfd, red->file, filefd, red->rhsfd, lhsfd);
		exit(1);
	}
	msh_err(msh, "dup2(%d, %d)", filefd , lhsfd);
	if (close(filefd) < 0)
	{
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
		exit(1);
	}
	return ;
}

static void	redir_write_fd(t_msh *msh,t_red *red, int lhsfd)
{
	msh_err(msh, "Redir(%d): %d>&%d.", ++gi, lhsfd, red->rhsfd);
	msh_err(msh, "dup2(%d, %d)", red->rhsfd , lhsfd);
	if (dup2(red->rhsfd, lhsfd) < 0)
	{
		msh_err(msh, "%d>&%d dup2(%d, %d), failed.",
			lhsfd, red->rhsfd, red->rhsfd, lhsfd);
		exit(1);
	}
	return ;
}

static void	redir_write(t_msh *msh, t_red *red, int lhsfd)
{
	if (red->file != NULL)
		redir_write_file(msh, red, lhsfd);
	else
		redir_write_fd(msh, red, lhsfd);
	return ;
}

void 		msh_outredirections(t_msh *msh, t_list *lst)
{
	t_red	*red;
	int		i;

	i = ft_lstsize(lst);
	while (i > 0)
	{
		red = (t_red*)ft_lstat(lst, i)->content;
		if (red->type == MTK_WRIT)
		{
			if (red->lhsfd == -2)
			{
				redir_write(msh, red, 1);
				redir_write(msh, red, 2);
			}
			else
				redir_write(msh, red, red->lhsfd);
		}
		else if (red->type == MTK_APND)
			redir_append(msh, red);
		i--;
	}
	return ;
}
