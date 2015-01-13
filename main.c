/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:19:51 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/13 10:03:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

/*
** TODO:
**	expand ~ ~+ from $home.
**	print errors.
**	builtins
**	*
*/

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>

void	msh_builtin_setenv(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}
void	msh_builtin_unsetenv(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}
void	msh_builtin_exit(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}

static void	handler(int s)
{
/* 	ft_putchar_fd('\n', 1); */
	(void)s;
	return ;
}

static int	from_string(int ac, char *av[])
{
	if (ac > 1 && ft_strequ("-c", av[1]))
		return (1);
	return (0);
}

int			main(int ac, char *av[])
{
	t_msh	msh;

	signal(SIGINT, &handler);
	if (msh_init_msh(&msh, av[0]))
		return (1);
	if (from_string(ac, av))
		msh_process_line(&msh, av[2]);
	else
	{
		if (msh.stdin_isatty)
			msh_header();
		msh_pause(&msh);
	}
	return (0);
}
