/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 10:11:51 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/09 14:26:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <minishell.h>

#define MSG_BUF_SIZE 25

static void	set_msg_index(char buf[MSG_BUF_SIZE], int i)
{
	const char	str[][MSG_BUF_SIZE] = {"Undefined Signal",

	"Hangup", "", "", "Illegal instruction", "Trace/BPT", "Abort trap",
	"EMT trap", "Floating point exception", "Killed", "Bus error",
	"Segmentation fault", "Bad system call", "", "Alarm clock",
	"Terminated", "Cputime limit exceeded", "Filesize limit exceeded",
	"Virtual timer expired", "Profiling timer expired",
	"User defined signal 1", "User defined signal 2"};
	ft_strcpy(buf, str[i]);
	D(int, i);
	D(char*, buf);
	return ;
}

static void	set_msg(char buf[MSG_BUF_SIZE], int sig)
{
	int			i;
	const int	tab[] = {0,

	SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT,
	SIGEMT, SIGFPE, SIGKILL, SIGBUS,
	SIGSEGV, SIGSYS, SIGPIPE, SIGALRM,
	SIGTERM, SIGXCPU, SIGXFSZ,
	SIGVTALRM, SIGPROF,
	SIGUSR1, SIGUSR2, -1};
	i = 0;
	while (tab[i] != -1 && tab[i] != sig)
		i++;
	if (sig == tab[i])
		set_msg_index(buf, i);
	else
		set_msg_index(buf, 0);
	return ;
}

int			msh_handle_signal(const t_msh *msh, const t_cmd *cmd)
{
	char	buf[MSG_BUF_SIZE];

	if (WIFEXITED(cmd->wstatus))
		return (1);
	else if (WIFSIGNALED(cmd->wstatus))
	{
		*buf = '\0';
		set_msg(buf, WTERMSIG(cmd->wstatus));
		ft_dprintf(2, "%s: %hhu\n", buf, WTERMSIG(cmd->wstatus));
		return (1);
	}
	(void)msh;
	return (0);
}
