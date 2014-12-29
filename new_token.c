/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 16:57:26 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/29 17:02:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

/*
** ''
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
	return (tot):
}

t_tkn			*msh_new_token(int type, char *line, t_tkn *tkn)
{
	tkn->type = type;
	tkn->ptr = line;
	if (type == MTK_FILE || type == MTK_CMD)
		tkn->len = ft_strcspn(line, "<>;| \t");
	else if (type >= MTK_HERE && type <= MTK_WRIT)
		tkn->len = redir_len(type, line);
	else if (type == MTK_SEMI || type == MTK_PIPE)
		tkn->len = 1;
	else if (type == MTK_END)
		tkn->len = 0;
	else
		tkn->len = ft_strcspn(line, " \t");
	return (tkn);
}


