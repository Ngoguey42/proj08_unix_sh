/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:21:38 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/27 15:28:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <libft.h>

# define ERRNO1ARGS 2, "%s, %s, %s\n", msh->shex, sys_errlist[errno]
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
	char		*mshex;
	char		**mshenv;
	char		**env;
}				t_msh;


int				msh_init_msh(t_msh *msh);

/*
** Env Manipulation.
*/
char 			**msh_get_envvarp(const t_msh *msh, const char *key);
char 			*msh_get_envvar(const t_msh *msh, const char *key);
void			msh_print_env(const t_msh *msh);
char			**msh_update_envvar(t_msh *msh, char *line);
char			**msh_new_envvar(t_msh *msh, char *line);
char			*msh_get_envvar(const t_msh *msh, const char *key);
char			**msh_get_envvarp(const t_msh *msh, const char *key);


#endif
