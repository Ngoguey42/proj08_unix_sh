
#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

/*
** Builtins Command Center.
*/
/*
** 'msh_is_builtin' searches for a builtin from a givent string.
** *
** 'msh_get_builtin_index' retrieves a builtin index from string.
** *
** 'msh_bi_init_pipeout' initiates stdout before a pipe-out.
**			'dup' => closed in 'msh_bi_disable_pipeout'.
**			'dup2' => closed in 'msh_bi_disable_pipeout'.
** *
** 'msh_bi_disable_pipeout' restores stdout after a pipe-out.
**			'dup2' => closed on next 'msh_bi_init_pipeout' OR msh exit.
** *
*/

t_bool		msh_is_builtin(const t_msh *msh, const char *cmd, size_t len)
{
	int		i;

	i = -1;
	while (msh->bi_n[++i][0] != '\0')
	{
		if (ft_strnequ(msh->bi_n[i], cmd, len))
			return (true);
	}
	return (false);
}

int			msh_get_builtin_index(const t_msh *msh, const char *cmd, size_t len)
{
	int		i;

	i = -1;
	while (msh->bi_n[++i][0] != '\0')
		if (ft_strnequ(msh->bi_n[i], cmd, len))
			return (i);
	msh_err(msh, "Could not retreive %.*r builtin.", len, cmd);
	return (0);
}

int			msh_bi_init_pipeout(t_msh *msh, t_cmd *cmd, int *fd1_savep)
{
	if ((*fd1_savep = dup(1)) < 0)
	{
		msh_err(msh, "Could not save stdout.");
		return (1);
	}
	if (dup2(cmd->rhspfd[1], 1) < 0)
	{
		msh_err(msh, "Could not set pipe out to stdout.");
		msh_bi_disable_pipeout(msh, cmd, *fd1_savep);
		return (1);
	}
	return (0);
}

void		msh_bi_disable_pipeout(t_msh *msh, t_cmd *cmd, int fd1_save)
{
	if (dup2(fd1_save, 1) < 0)
	{
		msh_err(msh, "Could not restore stdout.");
		exit(1);
	}
	if (close(fd1_save) < 0)
		msh_err(msh, "Could not close stdout dup.");
	(void)cmd;
}

