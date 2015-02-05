/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:21:38 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/05 09:55:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <libft.h>
/* #include <stdio.h> //debug */
#include <ft_debug.h> //debug

/* #define msh_err(env, format, args...) do {ft_putstr(format); } while (0) */

/* # define msh_err(...) ft_putstr("salut\n") */
/*
** ************************************************************************** **
** *
** Built-ins commands.
*/
# define NUMBUILTINS 5
# define MSHBIN_MAXN 9

# define PR(ARG) &msh_builtin_ ## ARG

# define MSHBIN_N {"cd", "setenv", "unsetenv", "env", "exit", ""}
# define MSHBIN_F {PR(cd), PR(setenv), PR(unsetenv), PR(env), PR(exit), NULL}

# define MSHENVINDEX 0x3

/*
** ************************************************************************** **
** *
** Misc
*/
# define MSH_PS1 "msh> "
# define MSH_PS2 "> "
# define MSH_PSHERE "h-doc> "

# define DEFAULT_PATH "PATH=/usr/bin:/bin"
# define FD_PATH "/dev/fd/"

/*
** ************************************************************************** **
** *
** Redirections
*/
# define OCREAT_FLAGS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

# define MSH_OP {"<<", ">>", "<", ">", ";", "|", ""}
# define NUMOPERATORS 6

# define MSH_LFDTOOLONG 0x01
# define MSH_LFDOVERLIM 0x02
# define MSH_LINVALID 0x04

# define MSH_RFDTOOLONG 0x08
# define MSH_RFDOVERLIM 0x10
# define MSH_RINVALID 0x20
# define MSH_RMISSING 0x40

/*
** ************************************************************************** **
** *
** Tokens types
** *
** MTK_IS2COP			is 2 char operator
** MTK_ISRDIN			is redirection in
** MTK_ISRDOUT			is redirection out
** MTK_ISRED			is redirection
** MTK_ISBRKO			is break operator
** MTK_ISBRK			is break
** MTK_ISWRDB			is word based
*/
# define MTK_HERE 0x1
# define MTK_APND 0x2
# define MTK_READ 0x3
# define MTK_WRIT 0x4
# define MTK_SEMI 0x5
# define MTK_PIPE 0x6

# define MTK_WORD 0x7
# define MTK_CMD 0x8
# define MTK_FILE 0x9
# define MTK_LVAR 0xa

# define MTK_END 0x10

# define MTK_IS2COP(A) ((A) == MTK_HERE || (A) == MTK_APND)
# define MTK_ISRDIN(A) ((A) == MTK_HERE || (A) == MTK_READ)
# define MTK_ISRDOUT(A) ((A) == MTK_APND || (A) == MTK_WRIT)
# define MTK_ISRED(A) ((A) <= MTK_WRIT && (A) >= MTK_HERE)
# define MTK_ISBRKO(A) ((A) == MTK_SEMI || (A) == MTK_PIPE)
# define MTK_ISBRK(A) ((A) == MTK_SEMI || (A) == MTK_PIPE || (A) == MTK_END)
# define MTK_ISWRDB(A) ((A) >= MTK_WORD && (A) <= MTK_LVAR)

# define MTKNAMES1 "HERE", "APND", "READ", "WRIT", "SEMI", "PIPE"
# define MTKNAMES {"", MTKNAMES1, "WORD", "CMD", "FILE", "LVAR", "END"}

# define RPFX(ARG) &msh_saveredir_ ## ARG
# define REDSAVEFUNCS {RPFX(here), RPFX(apnd), RPFX(read), RPFX(write)}

/*
** ************************************************************************** **
** *
**		'struct s_red'	One per redirection token.
**		type	type as in MTK_ defines.
**		lhsfd	left hand side file descriptor.		(-1) if all.
**		rhsfd	right hand side file descriptor.	(-2) if non existant.
**		file	right hand side file name.			NULL if non existant.
**		file_err	right hand side file, tested with ft_access tested.
**		hdoc	here document string.
**		error	errors encountered for this redirection:
**				0x1		lhsfd too long
**				0x2		lhsfd over limit
**				0x4		lhs  is invalid(unused)
**				0x8		rhsfd too long
**				0x10	rhsfd over limit
**				0x20	rhs is invalid
**				0x40	rhs missing
**		ptr		pointers of the two tokens into the user input
**		len		characters inside the two tokens.
**		prev_cp	for builtins, 'dup' of the previous destination fd.
**				>0 fd
**				0 unused
**				-1 error
**				-2 closed
*/
typedef struct	s_red
{
	int			type;
	int			lhsfd;
	int			rhsfd;
	char		*file;
	int			file_err;
	char		*hdoc;
	int			error;
	char		*ptr[2];
	size_t		len[2];
	int			prev_cp;
}				t_red;
/*
** ************************************************************************** **
** *
**		'struct s_tkn'	Token, as extracted from the input. (See tokenize.c)
**		type	type as in MTK_ defines.
**		ptr		pointer into the string.
**		len		token's length in 'ptr'.
*/
typedef struct	s_tkn
{
	int			type;
	char		*ptr;
	size_t		len;
}				t_tkn;
/*
** ************************************************************************** **
** *
**		'struct s_cmd'	One per command block. (See tokenize.c)
** *
**		atkn		tokens associated with the command block.
** *
**		ignore_env	for env -i
**		alvar		local variables
** *
**		is_builtin	boolean, whether cmd is a built-in or not.
**		bi_index	builtin function's index.
**		binerr		error regarding cmdpath's NULL value.
**		cmdpath		full path to the binary, NULL if not found.
**		wstatus		wait's return status.
** 		pid			child pid after fork.
** 		cmdav		argv to be sent.
**		avpad		padding in argv to apply
** *
**		ared		redirections
** *
**		iotypes		[0] in(left), [1] out(right) ; 0 == default, 1 == pipe.
**		lhspfd		Left Handed Side Pipe File Descriptors. (-2 == closed)
** 		lhspcmd		Left Handed Side Pipe t_CMD instance pointer.
**		rhspfd		Right Handed Side Pipe File Descriptors
** 		rhspcmd		Right Handed Side Pipe t_CMD instance pointer.
*/
# define STRU_S_CMD struct s_cmd

typedef struct	s_cmd
{
	t_list		*atkn[1];
	const char	*cmd_str;

	t_bool		ignore_env;
	t_list		*alvar[1];

	t_bool		is_builtin;
	int			bi_index;
	int			binerr;
	char		*cmdpath;
	int			wstatus;
	int			pid;
	char		**cmdav;
	size_t		avpad;

	t_list		*ared[1];

	int			iotypes[2];
	int			lhspfd[2];
	STRU_S_CMD	*lhspcmd;
	int			rhspfd[2];
	STRU_S_CMD	*rhspcmd;
}				t_cmd;
/*
** ************************************************************************** **
** *
** 'struct	s_msh' MiniSHell env.
** *
**		mshex		msh's binary name, from main's av[0].
** 		mshenv		pointer to sh's environ variable.
**		env			allocated msh's env.
** 		continue_	condition in input reading's loop.
**		bi_f		builtin_functions's array.
**		bi_n		buitin_name's array.
**		op			operators' list handled by msh.
**		red_f		redirections storing functions.
**		stdin_isatty	hide prompt and header if stdin in not a tty.
*/
# define CMSHS const struct s_msh
# define CMSH const t_msh

typedef struct	s_msh
{
	char		*mshex;
	char		**mshenv;
	char		**env;
	int			continue_;
	void		(*bi_f[NUMBUILTINS + 1])(struct s_msh *msh, t_cmd *cmd);
	char		bi_n[NUMBUILTINS + 1][MSHBIN_MAXN];
	char		op[NUMOPERATORS + 1][3];
	void		(*red_f[4])(CMSHS *msh, t_red *re, t_tkn *r, t_tkn *n);
	int			stdin_isatty;
}				t_msh;
typedef CMSH	t_mshc;
/*
** ************************************************************************** **
*/

/*
** Main functions.
*/
int				msh_init_msh(t_msh *msh, char *ex);
void			msh_pause(t_msh *msh);
void			msh_header(void);
void			msh_process_line(t_msh *msh, char *line);
void			msh_ps1(t_mshc *msh);
void			msh_ps2(t_mshc *msh, const char *d);

/*
** Tokenizations. (t_tkn / t_cmd / t_red)
*/
void			msh_tokenize(t_mshc *msh, t_list *atknp[1], char *line);
void			msh_split_cmd(t_mshc *msh, t_list *atknp[1], t_list *acmd[1]);
t_tkn			*msh_new_token(int type, char *line, t_tkn *tkn);

void			msh_cmd_get_av(t_mshc *msh, t_cmd *cmd);
void			msh_cmd_get_cmd(t_mshc *msh, t_cmd *cmd);
void			msh_cmd_get_redir(t_mshc *msh, t_cmd *cmd);
void			msh_cmd_get_heredoc(t_mshc *msh, t_cmd *cmd);
void			msh_cmd_get_locvar(t_mshc *msh, t_cmd *cmd);
void            msh_cmd_get_env_interpretation(t_mshc *msh, t_cmd *cmd);


int				msh_catch_syntax_errors(t_mshc *msh, const t_list *lst);

void			msh_expand_redir_tilde(t_mshc *msh, t_red *red);
void			msh_saveredir_here(t_mshc *m, t_red *red, t_tkn *r, t_tkn *n);
void			msh_saveredir_apnd(t_mshc *m, t_red *red, t_tkn *r, t_tkn *n);
void			msh_saveredir_read(t_mshc *m, t_red *red, t_tkn *r, t_tkn *n);
void			msh_saveredir_write(t_mshc *m, t_red *red, t_tkn *r, t_tkn *n);

/*
** Commands executions.
*/
int				msh_exec_cmd(t_msh *msh, t_list *lst);
int				msh_handle_signal(t_mshc *msh, const t_cmd *cmd);
void			msh_free_structs(t_mshc *msh, t_list *atkn[1], t_list *acmd[1]);
int				msh_cmd_error(t_mshc *msh, const t_cmd *cmd);

int				msh_exec_cmd_openpipe(t_mshc *msh, t_list *lst);
void			msh_exec_cmd_closepipel(t_mshc *msh, t_cmd *cmd);
void			msh_exec_cmd_closepiper(t_mshc *msh, t_cmd *cmd);

/*
** Child process commands.
*/
void			msh_exec_cmd_pipeout(t_mshc *msh, t_cmd *cmd);
void			msh_exec_cmd_pipein(t_mshc *msh, t_cmd *cmd);
int				msh_inredirections(t_mshc *msh, t_list *lst);
int				msh_outredirections(t_mshc *msh, t_list *lst);
void			msh_exec_cmd_update_env(t_msh *msh, t_cmd *cmd);
void			msh_free_env(t_msh *msh);

/*
** Environment.
*/
int				msh_del_envk(t_msh *msh, char *k);
char			**msh_new_envkv_m(t_msh *msh, char *k, char *v);
char			**msh_update_envkv_m(t_msh *msh, char *k, char *v);
char			**msh_update_envvar_m(t_msh *msh, char *line);
char			**msh_update_envvar(t_msh *msh, char *line);
char			**msh_new_envvar(t_msh *msh, char *line);
char			**msh_new_envvar_m(t_msh *msh, char *line);
char			*msh_get_envvar(t_mshc *msh, const char *key);
char			**msh_get_envvarp(t_mshc *msh, const char *key);
int				msh_isin_locvars(const char *kv, const t_list *lvars);
int				msh_delin_locvars(const char *kv, t_list *alvar[1]);
void			msh_print_env(t_mshc *msh, const t_cmd *cmd, int fd);
void			msh_update_pwd(t_msh *msh);

/*
** Builtins.
*/
t_bool			msh_is_builtin(t_mshc *msh, const char *cmd, size_t len);
int				msh_get_builtin_index(t_mshc *msh, const char *cmd,
						size_t len);
int				msh_builtin_init_fds(t_mshc *msh, t_cmd *cmd, int saves[2]);
void			msh_builtin_disable_fds(t_mshc *msh, t_cmd *cmd, int saves[2]);

int				msh_bi_init_pipeout(t_mshc *msh, t_cmd *cmd, int *fd1_savep);
void			msh_bi_disable_pipeout(t_mshc *msh, t_cmd *cmd, int fd1_save);
int				msh_bi_init_pipein(t_mshc *msh, t_cmd *cmd, int *fd0_savep);
void			msh_bi_disable_pipein(t_mshc *msh, t_cmd *cmd, int fd0_save);
int				msh_bi_init_redirs(t_mshc *msh, t_list *lst);
void			msh_bi_disable_redirs(t_mshc *msh, t_list *lst);

void			msh_builtin_cd(t_msh *msh, t_cmd *cmd);
void			msh_builtin_env(t_msh *msh, t_cmd *cmd);
void			msh_builtin_setenv(t_msh *msh, t_cmd *cmd);
void			msh_builtin_unsetenv(t_msh *msh, t_cmd *cmd);
void			msh_builtin_exit(t_msh *msh, t_cmd *cmd);

/*
** Errors:
*/
void			msh_err(t_mshc *msh, const char *format, ...);
void			msh_errmem(t_mshc *msh);
void			msh_cmd_err(t_mshc *msh, const t_cmd *cmd, int err);

/*
** Debug:
*/
void			msh_print_tokens(t_list *tkn);
void			msh_print_cmds(t_list *lst);
void			msh_print_lvar(t_list *lst);
void			msh_print_av(char **tab);
void			msh_print_redirs(t_list *lst);

#endif
