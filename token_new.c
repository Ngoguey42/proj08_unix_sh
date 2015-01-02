/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 16:57:26 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/30 08:01:08 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

/*
** 'redir_len' Calculates the len of a redirection, including prefix.
** 'msh_new_token' Edits 'tkn' for a given 'type' starting at 'line'.
*/

static size_t	redir_len(int type, char *line)
{
	size_t	tot;

	tot = 0;
	if (*line == '&' && (++tot))
		line++;
	else if (ft_isdigit(*line))
		while (ft_isdigit(*line) && (++tot))
			line++;
	if (type >= MTK_HERE && type <= MTK_APND && (tot += 2))
		line += 2;
	else if ((++tot))
		line++;
	return (tot);
}

t_tkn			*msh_new_token(int type, char *line, t_tkn *tkn)
{
	tkn->type = type;
	tkn->ptr = line;
	if (type == MTK_FILE || type == MTK_CMD || type == MTK_WORD)
		tkn->len = ft_strcspn(line, "<>;| \t");
	else if (type >= MTK_HERE && type <= MTK_WRIT)
		tkn->len = redir_len(type, line);
	else if (type == MTK_SEMI || type == MTK_PIPE)
		tkn->len = 1;
	else
		tkn->len = 0;
	return (tkn);
}
