/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_debug_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 10:32:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/22 10:32:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cmd2(const t_cmd *c)
{
	ft_dprintf(2, " ptr{%Kp}\n", c);
	ft_dprintf(2, "iotypes{%d, %d} lhspfd{%d, %d} rhspfd{%d, %d} ",
			c->iotypes[0], c->iotypes[1], c->lhspfd[0],
			c->lhspfd[1], c->rhspfd[0], c->rhspfd[1]);
	ft_dprintf(2, "(l/r)hspcmd{%p, %p}\n", c->lhspcmd, c->rhspcmd);
	ft_dprintf(2, "cpid{%d} ", c->pid);
	ft_dprintf(2, "wstatus{%d}\n", c->wstatus);
	return ;
}

void		msh_print_cmds(t_list *lst)
{
	t_cmd		*c;
	int			i;
	const char	bi_n[][MSHBIN_MAXN] = MSHBIN_N;

	i = 0;
	while (lst != NULL)
	{
		c = (t_cmd*)lst->content;
		ft_dprintf(2, "':RED:struct s_c:eof:#%d", ++i);
		if (c->is_builtin == true)
			ft_dprintf(2, " %Ks: \"%$K zr\"", "builtin", bi_n[c->bi_index]);
		else
			ft_dprintf(2, " \"%$K zr\" binerr(%Kd)", c->cmdpath, c->binerr);
		cmd2(c);
		msh_print_tokens(*c->atkn);
		msh_print_av(c->cmdav);
		msh_print_redirs(*c->ared);
		msh_print_lvar(*c->alvar);
		lst = lst->next;
		ft_putchar_fd('\n', 2);
	}
	return ;
}
