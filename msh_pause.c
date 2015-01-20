/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pause.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:41:37 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 10:00:52 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>

/*
** 'err_close_allfd' Called if 'fork' or 'pipe' failed in 'msh_exec_cmd'.
**		Only pipes-fd are left to be closed at this point.
**			(rhspfd / lhspfd).
**		'dup' used in builtins, are closed by builtins, even if error.
**		'dup2' to fd1 in builtins, are closed by builtins, even if error.
**	*
**		'open' called by childs are closed in situ.
**		'dup2' called by childs (pipes/redirections) are close by child.
** ***
** 'process_cmds'		For each t_cmd, prints error message or calls it.
** ***
** 'process_line' Processes a given 'char *line'.
**		Steps:
**		---Split 'char's into 't_list's of 't_tkn'.
**		------One 't_list' per 't_tkn'.
**		------Multiple 'char's per 't_tkn'
** *
**		---Split 't_tkn's into 't_list's of 't_cmd'.
**		------One 't_list' per 't_cmd'.
**		------Multiple 't_tkn's per 't_cmd'.
** *
**		---Extract informations from 't_tkn' into 't_cmd'.
**		------Command type and path. (Builtin/PATH's binary/Full path to binary)
**		------Redirections informations. (Stored into 't_list's of 't_red')
**		------Request user-input for here-documents.
**		---(if error == 0)
**		------Allocate command's 'char **argv'.
** *
**		---For each 't_cmd'
**		------Print error message.
**		----OR-
**		------Execute commands with pipes and redirections.
** ***
** 'msh_pause' Receives user input and calls 'process_line' on line at a time.
*/

static void err_close_allfd(t_mshc *msh, t_list *lst, t_cmd *cmd)
{
	t_cmd	*tmp_cmd;

	while (lst != NULL)
	{
		tmp_cmd = (t_cmd*)lst->content;
		if (tmp_cmd->lhspfd[0] > 0 || tmp_cmd->lhspfd[1] > 0)
			msh_exec_cmd_closepipel(msh, tmp_cmd);
		if (tmp_cmd->rhspfd[0] > 0 || tmp_cmd->rhspfd[1] > 0)
			msh_exec_cmd_closepiper(msh, tmp_cmd);
		if ((void*)cmd == lst->content)
			break ;
		lst = lst->next;
	}
	return ;
}

static void	process_cmds(t_msh *msh, t_list *alst[1])
{
	t_cmd	*cmd;
	t_list	*lst;

	lst = *alst;
	while (lst != NULL)
	{
		cmd = (t_cmd*)lst->content;
		if (msh_exec_cmd(msh, lst))
		{
			err_close_allfd(msh, *alst, cmd);
			return ;
		}
		lst = lst->next;
	}
	return ;
}

void		msh_process_line(t_msh *msh, char *line)
{
	t_list	*atkn[1];
	t_list	*acmd[1];

	*atkn = NULL;
	msh_tokenize(msh, atkn, line);
	if (msh_catch_syntax_errors(msh, *atkn))
	{
		msh_free_structs(msh, atkn, NULL);
		return ;
	}
	*acmd = NULL;
	msh_split_cmd(msh, atkn, acmd);
	process_cmds(msh, acmd);
	msh_free_structs(msh, atkn, acmd);
	return ;
}

void		msh_pause(t_msh *msh)
{
	char	*buf;
	int		ret;

	while (msh->continue_)
	{
/* 		msh_update_pwd(msh);//WHY IS IT HERE AREADY??? */
		msh_ps1(msh);
		if ((ret = get_next_line(0, &buf)) <= 0 || buf == NULL)
		{
			if (ret == 0)
			{
				if (msh->stdin_isatty)
					ft_putendl("exit");
			}
			else
				ft_dprintf(2, "%s: Error while reading Input.\n", msh->mshex);
			break ;
		}
		msh_process_line(msh, buf);
		free(buf);
	}
	return ;
}
