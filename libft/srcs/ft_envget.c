/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 08:22:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/20 11:25:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "libft.h"

char	**ft_envgetp(const char **env, const char *key)
{
	size_t		klen;
	size_t		klen2;

	if (env == NULL)
		return (NULL);
	if (ft_strchr(key, (int)'=') != NULL)
		klen = ft_strcharlen(key, '=');
	else
		klen = ft_strlen(key);
	while (*env != NULL)
	{
		klen2 = ft_strcharlen(*env, '=');
		klen2 = MAX(klen, klen2);
		if (ft_strnequ(*env, key, klen2))
			return ((char**)env);
		env++;
	}
	return (NULL);
}

char	*ft_envget(const char **env, const char *key)
{
	char **ret;

	ret = ft_envgetp(env, key);
	return (ret == NULL ? NULL : *ret);
}
