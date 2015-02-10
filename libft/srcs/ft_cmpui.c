/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 07:40:37 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/10 07:40:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cmpui_e(const void *a, const void *b)
{
	return (*(unsigned int*)a == *(unsigned int*)b);
}

int		ft_cmpui_l(const void *a, const void *b)
{
	return (*(unsigned int*)a < *(unsigned int*)b);
}

int		ft_cmpui_le(const void *a, const void *b)
{
	return (*(unsigned int*)a <= *(unsigned int*)b);
}

int		ft_cmpui_g(const void *a, const void *b)
{
	return (*(unsigned int*)a > *(unsigned int*)b);
}

int		ft_cmpui_ge(const void *a, const void *b)
{
	return (*(unsigned int*)a >= *(unsigned int*)b);
}
