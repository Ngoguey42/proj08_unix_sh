/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:46:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/21 07:52:45 by ngoguey          ###   ########.fr       */
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
	if (MTK_IS2COP(type) && (tot += 2))
		line += 2;
	else if ((++tot))
		line++;
	return (tot);
}

t_tkn			*msh_new_token(int type, char *line, t_tkn *tkn)
{
	tkn->type = type;
	tkn->ptr = line;
	if (MTK_ISWRDB(type))
		tkn->len = ft_strcspn(line, "<>;| \t");
	else if (MTK_ISRED(type))
		tkn->len = redir_len(type, line);
	else if (MTK_ISBRKO(type))
		tkn->len = 1;
	else
		tkn->len = 0;
	return (tkn);
}
