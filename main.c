/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:19:51 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 13:09:35 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
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
** exit return val
** remove exit on getcwdfail
** *debug
** free mem before execve
** free mem
** verif cette histoire de emacs

	#1 ls dans l1
	#2 ls -d de tous les lvl
	#3 Owrite in l3
	#4 Ocreate in l3
	#5 Owrite in l1
	#6 Ocreate in l1
	#7 Owrite in l2
	#8 Ocreate in l2
	#9 Cat in l1
	#10 Cat in l2
	#11 Cat in l3
	#12 cd dans tous les sens

X missing somewhere in tree, can't read dir, but can still wri/crea
W missing somewhere in tree, pas d'impact

ls: le contenu d'un sans R: noperm (suivant ok)
ls: le contenu d'un sans X: noperm (no suivant)
cat: un fichier dans un sans X: noperm
cd: dans un sans X, ou un dir dans sans X: noperm
owrite: dans un sans W: noperm
ocreate: dans un sans WX: noperm
seul les perm du dossier en cours importent pour les options de write


l1:
-wx #1 ls:noperm
	#2 OK
	#3 OK
	#4 OK
	#5 OK
	#6 OK
	#7 OK
	#8 OK
	#9 OK
	#10 OK
	#11 OK
	#12 OK

rw- #1 ls:noperm
	#2 l1 OK, then NOPERM
	#3 OK
	#4 OK
	#5 noperm
	#6 noperm
	#7 OK
	#8 OK
	#9 cat:noperm
	#10 OK
	#11 OK
	#12 cd: seul ./l1/.. fonctionne, tout le reste fail

r-x #1 OK
	#2 OK
	#3 OK
	#4 OK
	#5 OK
	#6 noperm
	#7 OK
	#8 OK
	#9 OK
	#10 OK
	#11 OK
	#12 OK

*/

static void	handler(int s)
{
	(void)s;
	return ;
}

static int	from_string(int ac, char *av[])
{
	if (av[1] != NULL && ft_strequ("-c", av[1]))
	{
		if (ac < 3)
		{
			msh_err(NULL, "-c: option requires an argument");
			exit(0);
		}
		return (1);
	}
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
