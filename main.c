/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:19:51 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/02 16:23:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define PUTL ft_putendl

/*
**	---main()	(main.c)
**	------msh_pause() (msh_pause.c)
**	---------get_next_line() (libft/srcs/get_next_line.c)
**	---------process_line()
**	------------msh_tokenize() (tokenize.c)
**	---------------new_token_type()
**	------------------msh_new_token() (token_new.c)
**	------------msh_split_cmd() (cmds_get.c)
**	---------------new_cmd()
**	------------------move_tokens()
**	------------------msh_cmd_get_cmd() (cmds_get_cmd.c)
**	------------------msh_cmd_get_redir() (cmds_get_redir.c)
**	---------------------extract_redir_and_file()
**	------------------------msh->red_f[type](cmds_get_redir_pertype.c)
**	------------------msh_cmd_get_heredoc() (cmds_get_heredoc.c)
**	------------------msh_cmd_get_av() (cmds_get_av.c)
**	------------msh_cmd_openfds() ()
**	------------msh_cmd_errors() (cmds_errprint.c)
**	------------msh_exec_cmds() (cmds_exec.c)
*/

void	msh_builtin_setenv(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}
void	msh_builtin_unsetenv(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}
void	msh_builtin_exit(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}

void		msh_header(void)
{
	PUTL(".___  ___.  __  .__   __.  __       _______. __    __     __ ");
	PUTL("|   \\/   | |  | |  \\ |  | |  |     /       ||  |  |  |   |  |");
	PUTL("|  \\  /  | |  | |   \\|  | |  |    |   (----`|  |__|  |   |  |");
	PUTL("|  |\\/|  | |  | |  . `  | |  |     \\   \\    |   __   |   |  |");
	PUTL("|  |  |  | |  | |  |\\   | |  | .----)   |   |  |  |  |   |__|");
	PUTL("|__|  |__| |__| |__| \\__| |__| |_______/    |__|  |__|   (__)");
}

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WTF(ARG, A2)	errno = 0;								\
	qprintf("REF: %18s %3d  ", ARG, access(ARG, A2), errno);	\
	qprintf("errno%2d: %s\n", errno, strerror(errno));			\
	ret = ft_access(ARG, A2);									\
	qprintf("CUS: %18s %3d  ", ARG, ret, ret);	\
	qprintf("errno%2d: %s\n\n", ret, strerror(ret))


int			main(int ac, char *av[])
{
	t_msh	msh;

/* 	char	*test; */
/* 	int		ret; */
/* 	ret = get_next_line(0, &test); */
/* 	if (ret <= 0) */
/* 	{ */
/* 		ft_dprintf(1, "STDOUT 1: %Hs\n", "Nothing in stdin."); */
/* 		ft_dprintf(2, "STDERR 2: %Is\n", "Nothing in stdin."); */
		
/* 	} */
/* 	else */
/* 	{ */
/* 		ft_dprintf(1, "STDOUT 1: %H_s\n", test); */
/* 		ft_dprintf(2, "STDERR 2: %I_s\n", test); */
		
/* 	} */
/* 	ft_putstr("end\n"); */

/* 	exit(1); */

	msh_header();
	if (msh_init_msh(&msh, av[0]))
		return (1);
/* 	msh_print_env(&msh);//debug; */
	msh_pause(&msh);
/* 	ft_memprint(&msh, sizeof(msh)); //debug */
	(void)ac;
	return (0);
}
