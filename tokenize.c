/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 12:50:28 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/29 16:57:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

#define IS_OP *line == ';' || *line == '|' || *line == '<' || *line == '>'
#define IS_FILE p[1] >= MTK_HERE && p[1] <= MTK_WRIT
#define IS_CMD p[0] == 0

static int		get_op(t_msh *msh, char *line)
{
	int		i;

	i = -1;
	while (msh->op[++i][0] != '\0')
	{
		if (ft_strnequ(line, msh->op[i], ft_strlen(msh->op[i])))
			break ;
	}
	if (msh->op[i][0] == '\0')
	{
		ft_dprintf(2, "Error, Operator not found\n");

	}
	return (i + 1);
}

static int		is_op(char *line)
{
	if (ft_isdigit(*line))
	{
		while (ft_isdigit(*line))
			line++;
		if (*line == '<' || *line == '>')
			return (1);
	}
	if ()
	return (0);
}

static int		new_token_type(t_list *atkn[1], char **line, int type)
{
	t_tkn	tkn;

	(void)msh_new_token(type, *line, &tkn);
	if (ft_lstnewback((t_list**)atkn, (void*)&tkn, sizeof(t_tkn)) == NULL)
		exit(1);
	*line += tkn.len;
/* 	qprintf("%s: %d %u %u \n", *line, type, tkn.len, ft_strcspn(*line, "<>;| \t")); */
	return (1);
}

/*
** 'msh_tokenize'
**		p[0]		command found.
**		p[1]		last token.
*/


void			msh_tokenize(t_msh *msh, t_list *atkn[1], char *line)
{
	int		p[2];

	ft_bzero(p, sizeof(p));
	while (*line != '\0')
	{
		if (ft_isblank(*line))
			line += ft_strspn(line, " \t");
		else if ((IS_OP) && (p[1] = get_op(msh, line)) &&
				new_token_type(atkn, &line, p[1]))
			p[0] = p[1] >= MTK_SEMI && p[1] <= MTK_PIPE ? 0 : p[0];
		else if ((IS_FILE) && new_token_type(atkn, &line, MTK_FILE))
			p[1] = MTK_FILE;
		else if ((IS_CMD) && new_token_type(atkn, &line, MTK_CMD) &&
				 (p[0] = 1))
			p[1] = MTK_CMD;
		else if (new_token_type(atkn, &line, MTK_WORD))
			p[1] = MTK_WORD;
	}
	new_token_type(atkn, &line, MTK_END);
}
