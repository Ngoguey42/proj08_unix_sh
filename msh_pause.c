/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 10:40:11 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/05 16:16:52 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>

/*
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
**		---Open pipes and redirections.
** *
**		---For each 't_cmd'
**		------Print error message.
**		----OR-
**		------Execute commands.
*/
/*
** 'msh_pause' Receives user input and calls 'process_line' on line at a time.
*/

static void err_close_allfd(t_msh *msh, t_list *lst, t_cmd *cmd)
{
	(void)msh;
	(void)lst;
	(void)cmd;
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
		if (!msh_cmd_errors(msh, cmd))
		{
			if (msh_exec_cmd(msh, lst))
			{
				err_close_allfd(msh, *alst, cmd);
				return ;
			}
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
	*acmd = NULL;
	msh_split_cmd(msh, atkn, acmd);
/* 	msh_print_cmds(*acmd);	//debug */
	process_cmds(msh, acmd);
/* 	msh_print_cmds(*acmd);	//debug */
	return ;
}

void		msh_pause(t_msh *msh)
{
	char	*buf;
	int		ret;

	while (msh->continue_)
	{
		ft_putstr(MSH_PS1);
		if ((ret = get_next_line(0, &buf)) <= 0 || buf == NULL)
		{
			if (ret == 0)
				ft_putendl("exit");
			else
				ft_dprintf(2, "%s: Error while reading Input.\n", msh->mshex);
			break ;
		}
		msh_process_line(msh, buf);
		free(buf);
	}
	return ;
}
