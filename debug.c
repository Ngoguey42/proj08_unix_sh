/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 16:09:27 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/30 10:01:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* #define FOR(a,b)    a; while (b) { (void)0 */
/* #define ENDFOR(c)    c; } */

void		msh_print_tokens(t_list *tkn)
{
	int			i;
	t_tkn		*c;
	const char	tktypes[][5] = MTKNAMES;

	i = 0;
	while (tkn != NULL)
	{
		c = (t_tkn*)tkn->content;
		ft_dprintf(2, "Token%H-2d: size%H0_2u %H4s \":BLU:", ++i,
			c->len, tktypes[c->type]);
		ft_dprintf(2, "% $.*zr", (int)c->len, c->ptr);
		ft_dprintf(2, ":eof::inv:%! $.*zr:eof:\"\n", 10, c->ptr + (int)c->len);
		tkn = tkn->next;
	}
	return ;
}

#define CMDPRINT(KEY, SUB) ft_dprintf(2, #KEY"(%"SUB") ", cmd->KEY)

void		msh_print_cmds(t_list *lst)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	while (lst != NULL)
    {
		cmd = (t_cmd*)lst->content;
		ft_dprintf(2, "'struct s_cmd'#%d \"%$K zr\"\n", ++i, cmd->cmdpath);
		msh_print_tokens(*cmd->atkn);
		lst = lst->next;
	}
	return ;
}
