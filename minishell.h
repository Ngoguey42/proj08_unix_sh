/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:21:38 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 12:22:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <limits.h>
# include <libft.h>

# define ERRNO1ARGS 2, "%s, %s, %s\n", pipex->ex, sys_errlist[errno]
# define ERRPRINTF_ERRNO(STR) ft_dprintf(ERRNO1ARGS, STR)

# define ERRNO2ARGS2(ERR) (ERR == -2 ? "Command not found" : sys_errlist[ERR])
# define ERRNO2ARGS(ERR) 2, "%s, %s, %s\n", pipex->ex, ERRNO2ARGS2(ERR)
# define ERRPRINTF_ERRNO2(ERR, STR) ft_dprintf(ERRNO2ARGS(ERR), STR)

/*
**		'struct s_cmd'
** 		cmdpath		full path to cmd's binary.
** 		cmdaccess		result of access testing for all 4 arguments:
** 						Error if ([0] != [3] != 0) || ([1] != [2] != -1)
** 		cmdav		cmd1's argv to be sent, built with ft_strsplit_s.
*/

typedef struct	s_cmd
{
	char		cmdpath[PATH_MAX + 1];
	int			cmdaccess;
	char		**cmdav;
	int			iotype[2];
	int			ioaccess[2];
	int			iofd[2];
	char		*iofile[2];
}				t_cmd;

/*
** 'struct	s_msh' MiniSHell env.
** *
**		shex		sh's binary name
** 		shenv		pointer to sh's environ variable, from parent shell.
**		env			sh's env.
*/

typedef struct	s_msh
{
	char		*shex;
	char		**shenv;
	char		**env;
}				t_msh;

#endif
