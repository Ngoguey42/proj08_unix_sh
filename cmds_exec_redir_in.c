
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <minishell.h>

static void	redir_redin_file(t_msh *msh,t_red *red)
{
	int		filefd;

	if ((filefd = open(red->file, O_RDONLY)) < 0)
	{
		msh_err(msh, "%d<%s redirection, failed.", red->lhsfd, red->file);
		exit(1);
	}
	if (dup2(filefd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d<%s dup2, failed.", red->lhsfd, red->file);
		exit(1);
	}
	if (close(filefd) < 0)
	{
		msh_err(msh, "%s(%d) close, failed.", red->file, filefd);
		exit(1);
	}
	return ;
}

static void	redir_redin_fd(t_msh *msh,t_red *red)
{
	if (dup2(red->rhsfd, red->lhsfd) < 0)
	{
		msh_err(msh, "%d<&%d dup2, failed.", red->lhsfd, red->rhsfd);
		exit(1);
	}
	return ;
}

static void	redir_heredoc(t_msh *msh,t_red *red)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		msh_err(msh, "here-document pipe, failed.");
		exit(1);
	}
	ft_putstr_fd(red->hdoc, pipefd[1]);
	if (close(pipefd[1]) < 0)
	{
		msh_err(msh, "here-doc pipe_in(%d) close, failed.", pipefd[1]);
		exit(1);
	}
	if (dup2(pipefd[0], red->lhsfd) < 0)
	{
		msh_err(msh, "here-doc dup2, failed.");
		exit(1);
	}
	if (close(pipefd[0]) < 0)
	{
		msh_err(msh, "here-doc pipe_out(%d) close, failed.", pipefd[0]);
		exit(1);
	}
	return ;
}

void 		msh_inredirections(t_msh *msh, t_list *lst)
{
	t_red	*red;

	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->type == MTK_READ)
		{
			if (red->file != NULL)
				redir_redin_file(msh, red);
			else
				redir_redin_fd(msh, red);
		}
		else if (red->type == MTK_HERE)
			redir_heredoc(msh, red);
		lst = lst->next;
	}
	return ;
}

