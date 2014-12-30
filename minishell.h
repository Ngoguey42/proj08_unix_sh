/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:21:38 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/30 11:16:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <libft.h>

/* # define ERRNO1ARGS 2, "%s, %s, %s\n", msh->shex, sys_errlist[errno] */
/* # define ERRPRINTF_ERRNO(STR) ft_dprintf(ERRNO1ARGS, STR) */

/* # define ERRNO2ARGS2(ERR) (ERR == -2 ? "Command not found" : sys_errlist[ERR]) */
/* # define ERRNO2ARGS(ERR) 2, "%s, %s, %s\n", pipex->ex, ERRNO2ARGS2(ERR) */
/* # define ERRPRINTF_ERRNO2(ERR, STR) ft_dprintf(ERRNO2ARGS(ERR), STR) */



/*
** 'built-in storing'
*/
# define MSHBIN_MAXN 9

# define MSHBI1N "cd"
# define MSHBI1F &msh_builtin_cd
# define MSHBI2N "setenv"
# define MSHBI2F &msh_builtin_setenv
# define MSHBI3N "unsetenv"
# define MSHBI3F &msh_builtin_unsetenv
# define MSHBI4N "env"
# define MSHBI4F &msh_builtin_env
# define MSHBI5N "exit"
# define MSHBI5F &msh_builtin_exit

# define MSHBIN_N {MSHBI1N, MSHBI2N, MSHBI3N, MSHBI4N, MSHBI5N, ""}
# define MSHBIN_F {MSHBI1F, MSHBI2F, MSHBI3F, MSHBI4F, MSHBI5F, NULL}

# define NUMBUILTINS 5

# define MSH_OP (char[][3]){"<<", ">>", "<", ">", ";", "|", ""}
# define NUMOPERATORS 6

# define MSH_PS1 "msh> "
# define MSH_PSHERE "h-doc> "

# define DEFAULT_PATH "PATH=/usr/bin:/bin"


# define MTK_HERE 0x1
# define MTK_APND 0x2
# define MTK_READ 0x3
# define MTK_WRIT 0x4
# define MTK_SEMI 0x5
# define MTK_PIPE 0x6

# define MTK_WORD 0x7
# define MTK_CMD 0x8
# define MTK_FILE 0x9

# define MTK_END 0xa

# define MTKNAMES1 "HERE", "APND", "READ", "WRIT", "SEMI", "PIPE"
# define MTKNAMES {"", MTKNAMES1, "WORD", "CMD", "FILE", "END"}

/*
**
*/

typedef struct	s_tkn
{
	int		type;
	char	*ptr;
	size_t	len;
}				t_tkn;

/*
**		'struct s_cmd'	For a command block
**		error		0 == no error.
**		atkn		pointer to the first token of the command block.
** 		cmdpath		full path to cmd's binary.
** 		cmdav		cmd1's argv to be sent.
**		iofds		in/out fd of command block. Default is {0, 1}.
*/

typedef struct	s_cmd
{
	int			error;
	int			binerror;
	t_list		*atkn[1];
	char		cmdpath[PATH_MAX + 1];
	int			is_built_in;
	char		**cmdav;
	int			iotypes[2];
	int			iofds[2];
}				t_cmd;

/*
** 'struct	s_msh' MiniSHell env.
** *
**		mshex		msh's binary name
**		mshstwd		msh's start working directory, from getcwd.
**		mshpath		msh's binary path, resolved from the shex and mshstwd.
** 		mshenv		pointer to sh's environ variable, from parent shell.
**		env			sh's env.
*/

typedef struct	s_msh
{
	char		*mshex;
	char		*mshstwd;
	char		mshpath[PATH_MAX - 1];
	char		**mshenv;
	char		**env;
	int			continue_;
	void		(*bi_f[NUMBUILTINS + 1])(struct s_msh *msh, t_cmd *cmd);
	char		bi_n[NUMBUILTINS + 1][MSHBIN_MAXN];
	char		op[NUMOPERATORS + 1][3];
}				t_msh;

typedef void	(*t_mshbi)(t_msh*, t_cmd*);

int				msh_init_msh(t_msh *msh, char *ex);
void			msh_pause(t_msh *msh);
void			msh_tokenize(t_msh *msh, t_list *atknp[1], char *line);
void			msh_split_cmd(t_msh *msh, t_list *atknp[1], t_list *acmd[1]);
t_tkn			*msh_new_token(int type, char *line, t_tkn *tkn);
void			msh_print_tokens(t_list *tkn);
void			msh_print_cmds(t_list *lst);
void			msh_err(t_msh *msh, const char *format, ...);


/*
** Env Manipulation.
*/
char			**msh_get_envvarp(const t_msh *msh, const char *key);
char			*msh_get_envvar(const t_msh *msh, const char *key);
void			msh_print_env(const t_msh *msh);
char			**msh_update_envvar_m(t_msh *msh, char *line);
char			**msh_new_envvar(t_msh *msh, char *line);
char			**msh_new_envvar_m(t_msh *msh, char *line);
char			*msh_get_envvar(const t_msh *msh, const char *key);
char			**msh_get_envvarp(const t_msh *msh, const char *key);

int				msh_resolve_binpath(t_msh *msh);

/*
** Built in functions.
*/
void    msh_builtin_cd(t_msh *msh, t_cmd *cmd);
void    msh_builtin_env(t_msh *msh, t_cmd *cmd);
void    msh_builtin_setenv(t_msh *msh, t_cmd *cmd);
void    msh_builtin_unsetenv(t_msh *msh, t_cmd *cmd);
void    msh_builtin_exit(t_msh *msh, t_cmd *cmd);


#endif
