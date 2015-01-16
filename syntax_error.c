/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:55:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/16 14:55:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** --
*/

int			msh_catch_syntax_errors(t_mshc *msh, const t_list *lst)
{
	const t_tkn	*tkn;
	const t_tkn	*next;

	if (lst == NULL)
		return (1);
	tkn = (const t_tkn*)lst->content;
	if (MTK_ISBRK(tkn->type))
		return (1);
	while (lst->next != NULL)
	{
		next = (const t_tkn*)lst->next->content;
		if (MTK_ISRED(tkn->type) && next->type != MTK_FILE)
			return (1);
		else if (MTK_ISBRK(tkn->type) && MTK_ISBRK(next->type) &&
					!(tkn->type == MTK_SEMI && tkn->type == MTK_END))
			return (1);
		lst = lst->next;
		tkn = (const t_tkn*)lst->content;
	}
	(void)msh;
	return (tkn->type == MTK_END ? 0 : 1);
}
