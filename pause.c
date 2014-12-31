/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 10:40:11 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 10:29:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>

static void	process_line(t_msh *msh, char *line)
{
	t_list	*atkn[1];
	t_list	*acmd[1];

	*atkn = NULL;
	msh_tokenize(msh, atkn, line);
/* 	msh_print_tokens(*atkn); */
	*acmd = NULL;
	msh_split_cmd(msh, atkn, acmd);
	msh_print_cmds(*acmd);
	msh_exec_cmds(msh, *acmd);
}

void		msh_pause(t_msh *msh)
{
	char	*buf;
	int		ret;

	while (msh->continue_)
	{
		ft_putstr(MSH_PS1);
		if ((ret = get_next_line(0, &buf)) <= 0 || buf == NULL)
		{
			if (ret == 0)
				ft_putendl("exit");
			else
				ft_dprintf(2, "%s: Error while reading Input.\n", msh->mshex);
			break ;
		}
/* 		ft_dprintf(2, "DEBUG %2u: '%$zr' '%0 $lr'\n", ft_strlen(buf), buf, buf); //debug */
		process_line(msh, buf);
		free(buf);
	}
	return ;
}
