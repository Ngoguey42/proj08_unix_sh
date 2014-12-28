/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 16:09:27 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/28 16:33:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		msh_print_tokens(t_list *tkn)
{
	int		i;
	t_tkn	*c;

	i = 0;
	while (tkn != NULL)
	{
		c = (t_tkn*)tkn->content;
		ft_dprintf(2, "Token%-2d: t%#0_4x s%0_2u \"%H $.*zr\"\n", ++i, c->type,
				   c->len, (int)c->len, c->ptr);
		tkn = tkn->next;
	}
}
