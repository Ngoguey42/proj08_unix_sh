/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 12:19:51 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/31 08:57:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define PUTL ft_putendl

void	msh_builtin_cd(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}
void	msh_builtin_env(t_msh *msh, t_cmd *cmd){(void)msh; (void)cmd;}
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

	msh_header();



	if (msh_init_msh(&msh, av[0]))
		return (1);
/* 	msh_print_env(&msh);//debug; */
	msh_pause(&msh);
/* 	ft_memprint(&msh, sizeof(msh)); //debug */
	(void)ac;
	return (0);
}
