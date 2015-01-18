/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:26:37 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/16 14:52:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

static void	free_redlst(void *content, size_t size)
{
	t_red	*red;

	red = (t_red*)content;
	if (red->file != NULL)
		free(red->file);
	if (red->hdoc != NULL)
		free(red->hdoc);
	free(content);
	(void)size;
	return ;
}

static void	free_av(char **av)
{
	char	**start;

	start = av;
	while (*av != NULL)
		free(*av++);
	free(start);
	return ;
}

static void	free_cmdlst(void *content, size_t size)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)content;
	if (cmd->cmdpath != NULL)
		free(cmd->cmdpath);
	if (cmd->atkn != NULL)
		ft_lstdel(cmd->atkn, &ft_lstfreecont);
	if (cmd->ared != NULL)
		ft_lstdel(cmd->ared, &free_redlst);
	if (cmd->cmdav != NULL)
		free_av(cmd->cmdav);
	free(content);
	(void)size;
	return ;
}

void		msh_free_structs(t_mshc *msh, t_list *atkn[1], t_list *acmd[1])
{
	if (atkn != NULL)
		ft_lstdel(atkn, &ft_lstfreecont);
	if (acmd != NULL)
		ft_lstdel(acmd, &free_cmdlst);
	(void)msh;
	return ;
}
