/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_get_redir_pertype.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 07:45:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/16 07:29:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

void		msh_saveredir_here(t_mshc *msh, t_red *red, t_tkn *tkn, t_tkn *n)
{
	red->error |= extract_nbr(tkn->ptr, &red->lhsfd, 0);
	if (n->type != MTK_FILE)
		red->error |= MSH_RINVALID;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)n->ptr, n->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		msh_expand_redir_tilde(msh, red);
		red->file[n->len] = '\0';
	}
	return ;
}

void		msh_saveredir_apnd(t_mshc *msh, t_red *red, t_tkn *tkn, t_tkn *n)
{
	red->error |= extract_nbr(tkn->ptr, &red->lhsfd, 1);
	if (n->type != MTK_FILE || n->len == 0)
		red->error |= MSH_RINVALID;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)n->ptr, n->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[n->len] = '\0';
		msh_expand_redir_tilde(msh, red);
		if (red->file_err || (red->file_err = ft_access(red->file, W_OK)) != 0)
			red->error |= MSH_RINVALID;
	}
	return ;
}

void		msh_saveredir_read(t_mshc *msh, t_red *red, t_tkn *tkn, t_tkn *n)
{
	red->error |= extract_nbr(tkn->ptr, &red->lhsfd, 0);
	if (n->type != MTK_FILE)
		red->error |= MSH_RINVALID;
	else if (*n->ptr == '&')
		red->error |= extract_nbr(n->ptr + 1, &red->rhsfd, -1) << 3;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)n->ptr, n->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[n->len] = '\0';
		msh_expand_redir_tilde(msh, red);
		if (red->file_err || (red->file_err = ft_access(red->file, R_OK)) != 0)
			red->error |= MSH_RINVALID;
	}
	return ;
}

void		msh_saveredir_write(t_mshc *msh, t_red *red, t_tkn *tkn, t_tkn *n)
{
	if (*tkn->ptr == '&')
		red->lhsfd = -1;
	else
		red->error |= extract_nbr(tkn->ptr, &red->lhsfd, 1);
	if (n->type != MTK_FILE)
		red->error |= MSH_RINVALID;
	else if (*n->ptr == '&')
		red->error |= extract_nbr(n->ptr + 1, &red->rhsfd, -1) << 3;
	else
	{
		red->rhsfd = -2;
		red->file = ft_memdup((void*)n->ptr, n->len + 1);
		if (red->file == NULL)
			msh_errmem(msh);
		red->file[n->len] = '\0';
		msh_expand_redir_tilde(msh, red);
		if (red->file_err || (red->file_err = ft_access(red->file, W_OK)) != 0)
			red->error |= MSH_RINVALID;
	}
	return ;
}
