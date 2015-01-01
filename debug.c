/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 16:09:27 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/01 17:18:39 by ngoguey          ###   ########.fr       */
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

void		msh_print_av(char **tab)
{
	int		i;
	int		ret;

	if (tab == NULL)
		ft_dprintf(2, "AV pointer to NULL.\n");
	else if (*tab == NULL)
		ft_dprintf(2, "No AV to send.\n");
	i = -1;
	while (tab != NULL && *tab != NULL)
	{
		ft_dprintf(2, "av[:YEL::red:");
		ret = ft_dprintf(2, "%d", ++i);
		ft_dprintf(2, ":eof:]");
		ft_dprintf(2, "%*s\"%J $zr\" \n", 6 - ret, " == ", *tab);
		tab++;
	}
	return ;
}

void		msh_print_redirs(t_list *lst)
{
	int		i;
	t_red	*red;

	i = 0;
	while (lst != NULL)
	{
		red = (t_red*)lst->content;
		ft_dprintf(2, "Redirection#%Nd: Type:%N#x  ", ++i, red->type);
		ft_dprintf(2, "lfd(%3d) ", red->lhsfd);
		if (red->file != NULL)
			ft_dprintf(2, "rfile:\"%!N $zr\" ", red->file);
		else
			ft_dprintf(2, "rfd(%3d) ", red->rhsfd);
		ft_dprintf(2, "err:%.6b", red->error);
		ft_putchar_fd('\n', 2);
		lst = lst->next;
	}

}

#define CMDPRINT(KEY, SUB) ft_dprintf(2, #KEY"(%"SUB") ", cmd->KEY)

void		msh_print_cmds(t_list *lst)
{
	t_cmd		*cmd;
	int			i;
	const char	bi_n[][MSHBIN_MAXN] = MSHBIN_N;

	i = 0;
	while (lst != NULL)
    {
		cmd = (t_cmd*)lst->content;
		ft_dprintf(2, "':RED:struct s_cmd:eof:#%d", ++i);
		if (cmd->is_builtin == true)
			ft_dprintf(2," %Ks: \"%$K zr\"\n", "builtin", bi_n[cmd->bi_index]);
		else
			ft_dprintf(2," \"%$K zr\" binerr(%Kd)\n", cmd->cmdpath, cmd->binerr);
		msh_print_tokens(*cmd->atkn);
		msh_print_av(cmd->cmdav);
		msh_print_redirs(*cmd->ared);
		lst = lst->next;
	}
	return ;
}
