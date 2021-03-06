/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 11:38:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ft_math.h>
#include <minishell.h>

/*
** 'concat' Concatenates user's inputs.
** 'request_heredoc' Requests user input for here document
** 'msh_cmd_get_heredoc' Parses t_red's list for here-documents. ('<<')
*/

static char	*concat(char *rhs, char *lhs)
{
	char	*ret;
	size_t	len;

	if (rhs == NULL)
		len = ft_strlen(lhs) + 1;
	else
		len = ft_strlen(rhs) + ft_strlen(lhs) + 1;
	ret = (char*)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		msh_errmem(NULL);
	*ret = '\0';
	if (rhs != NULL)
		ft_strcpy(ret, rhs);
	ft_strcat(ret, lhs);
	ft_strcat(ret, "\n");
	ret[len] = '\0';
	return (ret);
}

static void	request_heredoc(t_mshc *msh, t_red *red)
{
	char	*line;
	int		ret;
	char	*cat;

	msh_ps2(msh, MSH_PSHERE);
	cat = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strnequ(red->ptr[1], line, MAX((int)red->len[1],
				(int)ft_strlen(line))))
			break ;
		cat = concat(cat, line);
		msh_ps2(msh, MSH_PSHERE);
	}
	if (ret < 0)
	{
		msh_err(msh, "%d", sys_errlist[EIO]);
		exit(0);
	}
	red->hdoc = cat;
	return ;
}

void		msh_cmd_get_heredoc(t_mshc *msh, t_cmd *cmd)
{
	t_list	*lst;
	t_red	*red;

	if (!cmd->ared)
		return ;
	lst = *cmd->ared;
	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		if (red->type == MTK_HERE && (red->error & MSH_RINVALID) == 0 &&
			(red->error & MSH_RMISSING) == 0)
			request_heredoc(msh, red);
		lst = lst->next;
	}
	return ;
}
