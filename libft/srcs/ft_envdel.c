/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 10:44:55 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 11:27:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include "libft.h"

int			ft_envdel(char **env, const char *key)
{
	char	*line;
	size_t	envlen;

	if (env == NULL)
		return (1);
	line = ft_envget((const char**)env, key);
	if (line == NULL)
		return (1);
	envlen = 0;
	while (env[envlen] != NULL)
		envlen++;
	while (*env != line)
		envlen--;
		env++;
	ft_memmove(env, env + 1, envlen * sizeof(char*));
	return (0);
}
