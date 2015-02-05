/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:55:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/05 09:09:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** --
*/

#define STX_ERR_MSH "syntax error near unexpected token"

static int	red_no_file(t_mshc *msh, const t_tkn *tkn, const t_tkn *next)
{
	if (MTK_ISRED(tkn->type) && next->type != MTK_FILE)
	{
		msh_err(msh, "%s `%!$ .1r'", STX_ERR_MSH, (char*)next->ptr);
		return (1);
	}
	return (0);
}

static int	red_bad_allwrite(t_mshc *msh, const t_tkn *tkn, const t_tkn *next)
{
	if (MTK_ISRED(tkn->type) && *tkn->ptr == '&' && *next->ptr == '&')
	{
		msh_err(msh, "%s `%!$ .1r'", STX_ERR_MSH, (char*)next->ptr);
		return (1);
	}
	return (0);
}

static int	bad_breaks(t_mshc *msh, const t_tkn *tkn, const t_tkn *next)
{
	if (MTK_ISBRK(tkn->type) && MTK_ISBRK(next->type) &&
		!(tkn->type == MTK_SEMI && next->type == MTK_END))
	{
		msh_err(msh, "%s `%!$ .1r'", STX_ERR_MSH, (char*)next->ptr);
		return (1);
	}
	return (0);
}

int			msh_catch_syntax_errors(t_mshc *msh, const t_list *lst)
{
	const t_tkn	*tkn;
	const t_tkn	*next;

	if (lst == NULL)
		return (1);
	tkn = (const t_tkn*)lst->content;
	if (MTK_ISBRKO(tkn->type))
	{
		msh_err(msh, "%s `%!$ .1r'", STX_ERR_MSH, (char*)tkn->ptr);
		return (1);
	}
	while (lst->next != NULL)
	{
		next = (const t_tkn*)lst->next->content;
		if (red_no_file(msh, tkn, next) ||
			red_bad_allwrite(msh, tkn, next) ||
			bad_breaks(msh, tkn, next))
			return (1);
		lst = lst->next;
		tkn = (const t_tkn*)lst->content;
	}
	(void)msh;
	return (tkn->type == MTK_END ? 0 : 1);
}
