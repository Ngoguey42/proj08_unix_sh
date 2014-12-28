/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 10:40:11 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/28 12:50:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <minishell.h>


static void	process_line(t_msh *msh, char *line)
{
	t_list	*tkn;

	tkn = NULL;
	msh_tokenize(msh, &tkn);
	(void)atkn;
	(void)msh;
	(void)line;
	
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
				ft_dprintf(2, "%s: Received EOF, bye bye.\n", msh->mshex);
			else
				ft_dprintf(2, "%s: Error while reading Input.\n", msh->mshex);
			break ;
		}
		ft_dprintf(2, "DEBUG %2u: '%$zr' '%0 $lr'\n", ft_strlen(buf), buf, buf); //debug
		if (buf == NULL)
		process_line(msh, buf);
		free(buf);
	}
	return ;
}
