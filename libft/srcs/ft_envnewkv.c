/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envnewkv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 09:31:23 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/28 11:26:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*cat(char *k, char *v)
{
	char	*ret;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(k) + ft_strlen(v) + 2));
	if (!ret)
		return (NULL);
	*ret = '\0';
	ft_strcpy(ret, k);
	ft_strcat(ret, "=");
	ft_strcat(ret, v);
	return (ret);
}

char			**ft_envnewkv_m(char ***env, char *k, char *v)
{
	size_t	count;
	char	**newenv;

	count = 0;
	while ((*env)[count] != NULL)
		count++;
	if ((newenv = (char**)malloc(sizeof(char*) * (count + 2))) == NULL)
		return (NULL);
	if ((newenv[count] = cat(k, v)) == NULL)
	{
		free(newenv);
		return (NULL);
	}
	newenv[count + 1] = NULL;
	count = 0;
	while ((*env)[count] != NULL)
	{
		newenv[count] = (*env)[count];
		count++;
	}
	free(*env);
	*env = newenv;
	return (*env + count);
}

char			**ft_envupdatekv_m(char ***env, char *k, char *v)
{
	char	**ptr;

	ptr = ft_envgetp((const char**)*env, k);
	if (ptr == NULL)
		return (ft_envnewkv_m(env, k, v));
	free(*ptr);
	*ptr = cat(k, v);
	if (*ptr == NULL)
		return (NULL);
	return (ptr);
}
