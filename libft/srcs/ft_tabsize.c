/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 08:26:30 by ngoguey           #+#    #+#             */
/*   Updated: 2014/11/24 08:26:41 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tabsize(void **tab)
{
	t_tabdt	*s;

	if (!(s = ft_tabcc(tab)))
		return (0);
	return (s->size);
}
