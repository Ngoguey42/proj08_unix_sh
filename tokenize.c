/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 12:50:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/21 07:55:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

#define IS_OP *line == ';' || *line == '|' || *line == '<' || *line == '>'
#define IS_FILE MTK_ISRED(p[1])
#define IS_CMD p[0] == 0

/*
**	Tokenization:	MTK_ = Minishell ToKen_
**	  Operators:
**	  --Redirections:
**	  ----In:
**	  ------MTK_HERE '[digits]<<'
**	  ------MTK_READ '[digits]<'
**	  ----Out:
**	  ------MTK_APND '[digits]>>'
**	  ------MTK_WRIT '[digits|&]>'
**    --Command bocks splitters:
**	  ----MTK_SEMI ';'
**	  ----MTK_PIPE '|'
**	  Words:
**	  --MTK_CMD	'cmd_name|bin_path'
**	  --MTK_FILE 'file_path|&fd'
**	  --MTK_WORD 'word'
**	  Special tokens:
**	  --MTK_END '\0'
** *
**	Rules:
**	--A 'Command block' is delimited by:
**			- MTK_SEMI
**			- MTK_PIPE
**			- line beginning
**			- line end '\0'
**	--A token end is delimited by:
**			- line beginning.
**			- an 'isblank' character (<SPACE> || \t)
**			- an 'operator start'
**			- line end '\0'.
**	--Successives isblank characters are ignored.
**	--A token is an MTK_WORD if it doesn't meet any rule below.
**	--A token is an Operator if an operator pattern is detected.
**	--A word following a redirection is an MTK_FILE.
**	--The first MTK_WORD of a Command block, is an MTK_CMD.
*/

/*
** 'get_op' returns the TNK_ type once a token has been ID as an Operator.
** 'is_op' determines if the token starting at 'line' is an Operator.
** 'new_token_type' mallocs a new link one a token has beed ID.
** 'msh_tokenize' parses line splitting it into tokens.
**		p[0]		Is MTK_CMD found in current command block.
**		p[1]		Last MTK_ in line.
*/

static int		get_op(t_mshc *msh, char *line)
{
	int		i;

	i = -1;
	if (*line == '&')
		line++;
	else if (ft_isdigit(*line))
		while (ft_isdigit(*line))
			line++;
	while (msh->op[++i][0] != '\0')
	{
		if (ft_strnequ(line, msh->op[i], ft_strlen(msh->op[i])))
			break ;
	}
	if (msh->op[i][0] == '\0')
	{
		ft_dprintf(2, "Error, Operator not found\n");
		exit(1);
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
	else if (*line == '&' && line[1] == '>' && line[2] != '>')
		return (1);
	else if (*line == '>' || *line == '<' || *line == ';' || *line == '|')
		return (1);
	return (0);
}

static int		new_token_type(t_list *atkn[1], char **line, int type)
{
	t_tkn	tkn;

	ft_bzero(&tkn, sizeof(t_tkn));
	(void)msh_new_token(type, *line, &tkn);
	if (ft_lstnewback((t_list**)atkn, (void*)&tkn, sizeof(t_tkn)) == NULL)
		exit(1);
	*line += tkn.len;
	return (1);
}

void			msh_tokenize(t_mshc *msh, t_list *atkn[1], char *line)
{
	int		p[2];

	ft_bzero(p, sizeof(p));
	while (*line != '\0')
	{
		if (ft_isblank(*line))
			line += ft_strspn(line, " \t");
		else if (is_op(line) && (p[1] = get_op(msh, line)) &&
				new_token_type(atkn, &line, p[1]))
			p[0] = MTK_ISBRKO(p[1]) ? 0 : p[0];
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
