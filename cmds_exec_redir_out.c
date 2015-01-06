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

/*
** 'redir_append' Sets up '>>FILE' redirection.
** 'redir_write_file' Sets up '>&FILE' redirection.
** 'redir_write_file_all' Sets up '&>FILE' redirection.
** 'redir_write_fd' Sets up '>&fd' redirection.
** 'msh_outredirections' Parses t_red's list for the above in redirections.
*/

int g_i; //debug

static void	redir_append(t_msh *msh,t_red *red)
{
	int		filefd;

	msh_err(msh, "Redir(%d): %d>>%! $r.", ++g_i, red->lhsfd, red->file);
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

	msh_err(msh, "Redir(%d): %d>%! $r.", ++g_i, red->lhsfd, red->file);
	if ((filefd = open(red->file, O_WRONLY)) < 0)
	{
		msh_err(msh, "%d>%!r open, failed.", red->lhsfd, red->file);
		exit(1);
	}
	msh_err(msh, "fd(%d) = open(%! $r)", filefd , red->file);
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			red->lhsfd, red->file, filefd, filefd, red->lhsfd);
		exit(1);
	}
	msh_err(msh, "dup2(%d, %d)", filefd , red->lhsfd);
	if (close(filefd) < 0)
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
	return ;
}

static void	redir_write_file_all(t_msh *msh, t_red *red)
{
	int		filefd;

	msh_err(msh, "Redir(%d): &>%! $r.", ++g_i, red->file);
	if ((filefd = open(red->file, O_WRONLY)) < 0)
	{
		msh_err(msh, "&>%!r open, failed.", red->file);
		exit(1);
	}
	msh_err(msh, "fd(%d) = open(%! $r)", filefd , red->file);
	if (dup2(filefd, 1) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			1, red->file, filefd, filefd, 1);
		exit(1);
	}
	msh_err(msh, "dup2(%d, %d)", filefd , 1);
	if (dup2(filefd, 2) < 0)
	{
		msh_err(msh, "%d>%!r(%d) dup2(%d, %d), failed.",
			2, red->file, filefd, filefd, 2);
		exit(1);
	}
	msh_err(msh, "dup2(%d, %d)", filefd , 2);
	if (close(filefd) < 0)
		msh_err(msh, "%!r(%d) close, failed.", red->file, filefd);
	return ;
}

static void	redir_write_fd(t_msh *msh,t_red *red)
{
	msh_err(msh, "Redir(%d): %d>&%d.", ++g_i, red->lhsfd, red->rhsfd);
	msh_err(msh, "dup2(%d, %d)", red->rhsfd , red->lhsfd);
	if (dup2(red->rhsfd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d>&%d dup2(%d, %d), failed.",
			red->lhsfd, red->rhsfd, red->rhsfd, red->lhsfd);
		exit(1);
	}
	return ;
}

void 		msh_outredirections(t_msh *msh, t_list *lst)
{
	t_red	*red;
	
	g_i = 0;
	// int		i;
	// int		j;

	// i = ft_lstsize(lst);
	// j = ft_lstsize(lst);
	// i = 1;
	// while (i <= j)
	while (lst != NULL)
	{
		// red = (t_red*)ft_lstat(lst, i)->content;
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
		// i--;
		// i++;
		lst = lst->next;
	}
	return ;
}
