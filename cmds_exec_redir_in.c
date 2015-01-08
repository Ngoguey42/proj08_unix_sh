/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_redir_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 15:05:43 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/08 12:29:21 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <minishell.h>

/*
** 'redir_redin_file' Sets up '<FILE' redirection.
**			'open' => closed here.
**			'dup2' => closed by child.
** 'redir_redin_fd' Sets up '<&FD' redirection.
**			'dup2' => closed by child.
** 'redir_heredoc' Sets up '<<KEYWORD' redirection, inputrecorded in red->hdoc.
**			'pipe' => both closed here.
**			'dup2' => closed by child.
** 'msh_inredirections' Parses t_red's list for the above in redirections.
*/

static int	redir_redin_file(t_msh *msh, t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_RDONLY)) < 0)
	{
		msh_err(msh, "%d<%s redirection, failed.", red->lhsfd, red->file);
		return (1);
	}
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d<%s dup2, failed.", red->lhsfd, red->file);
		return (close(filefd), 1);
	}
	if (close(filefd) < 0)
		msh_err(msh, "%s(%d) close, failed.", red->file, filefd);
	return (0);
}

static int	redir_redin_fd(t_msh *msh, t_red *red)
{
	if (dup2(red->rhsfd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d<&%d dup2, failed.", red->lhsfd, red->rhsfd);
		return (1);
	}
	return (0);
}

static int	redir_heredoc(t_msh *msh, t_red *red)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		msh_err(msh, "here-document pipe, failed.");
		return (1);
	}
	ft_putstr_fd(red->hdoc, pipefd[1]);
	if (close(pipefd[1]) < 0)
		msh_err(msh, "here-doc pipe_in(%d) close, failed.", pipefd[1]);
	if (dup2(pipefd[0], red->lhsfd) < 0)
	{
		msh_err(msh, "here-doc dup2, failed.");
		return (close(pipefd[0]), 1);
	}
	if (close(pipefd[0]) < 0)
		msh_err(msh, "here-doc pipe_out(%d) close, failed.", pipefd[0]);
	return (0);
}

int			msh_inredirections(t_msh *msh, t_list *lst)
{
	t_red	*red;
	int		ret;

	ret = 0;
	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->type == MTK_READ)
		{
			if (red->file != NULL)
				ret = redir_redin_file(msh, red);
			else
				ret = redir_redin_fd(msh, red);
		}
		else if (red->type == MTK_HERE)
			ret = redir_heredoc(msh, red);
		if (ret)
			return (1);
		lst = lst->next;
	}
	return (0);
}
