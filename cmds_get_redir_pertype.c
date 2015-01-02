/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_get_redir_pertype.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/01 13:55:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/02 14:35:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** 'extract_nbr' Extracts a filedescriptor from a given str 'ptr'.
**		ERRORS Cases:
**		if len >= 10^9
**			error = too long
**		else if isdigit && len > 255
**			error = over limit
**		else if !isdigit && !(*str is operator)
**			error = invalid.
** *
**		VALID Cases:
**		if isdigit && len <= 255
**			fd = atoi(ptr)
**		else if !isdigit && *str == operator (== is lhs)
**			fd = default
*/
/*
** 'msh_saveredir_here' [digits]<<keyword
** *
** 'msh_saveredir_apnd' [digits]>>file
** *
** 'msh_saveredir_read' [digits]<{&digits|file}
** *
** 'msh_saveredir_write' [digits|&]>{&digits|file}
** *
*/

static int	extract_nbr(const char *ptr, int *fdp, int def)
{
	int	error;

	error = 0;
	if (ft_strspn(ptr, "0123456789") > 9)
		error = MSH_LFDTOOLONG;
	else if (ft_isdigit(*ptr))
	{
		*fdp = ft_atoi(ptr);
		if (*fdp > 255)
			error = MSH_LFDOVERLIM;
	}
	else if (def > 0 && (*ptr == '<' || *ptr == '>'))
		*fdp = def;
	else
		error = MSH_LINVALID;
	return (error);
}

void	msh_saveredir_here(t_msh *msh, t_red *red, t_tkn *redir, t_tkn *next)
{
	red->error |= extract_nbr(redir->ptr, &red->lhsfd, 0);
	if (next->type != MTK_FILE)
		red->error |= MSH_RINVALID;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)next->ptr, next->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[next->len] = '\0';
	}
	return ;
}

void	msh_saveredir_apnd(t_msh *msh, t_red *red, t_tkn *redir, t_tkn *next)
{
	red->error |= extract_nbr(redir->ptr, &red->lhsfd, 1);
	if (next->type != MTK_FILE || next->len == 0)
		red->error |= MSH_RINVALID;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)next->ptr, next->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[next->len] = '\0';
	}
	return ;
}

void	msh_saveredir_read(t_msh *msh, t_red *red, t_tkn *redir, t_tkn *next)
{
	red->error |= extract_nbr(redir->ptr, &red->lhsfd, 0);
	if (next->type != MTK_FILE)
		red->error |= MSH_RINVALID;
	else if (*next->ptr == '&')
		red->error |= extract_nbr(next->ptr + 1, &red->rhsfd, -1) << 3;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)next->ptr, next->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[next->len] = '\0';
	}
	return ;
}

void	msh_saveredir_write(t_msh *msh, t_red *red, t_tkn *redir, t_tkn *next)
{
	if (*redir->ptr == '&')
		red->lhsfd = -1;
	else
		red->error |= extract_nbr(redir->ptr, &red->lhsfd, 1);
	if (next->type != MTK_FILE)
		red->error |= MSH_RINVALID;
	else if (*next->ptr == '&')
		red->error |= extract_nbr(next->ptr + 1, &red->rhsfd, -1) << 3;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)next->ptr, next->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[next->len] = '\0';
	}
	return ;
}
