/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 07:40:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/10 07:44:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cmpi_e(const void *a, const void *b)
{
	return (*(int*)a == *(int*)b);
}

int		ft_cmpi_l(const void *a, const void *b)
{
	return (*(int*)a < *(int*)b);
}

int		ft_cmpi_le(const void *a, const void *b)
{
	return (*(int*)a <= *(int*)b);
}

int		ft_cmpi_g(const void *a, const void *b)
{
	return (*(int*)a > *(int*)b);
}

int		ft_cmpi_ge(const void *a, const void *b)
{
	return (*(int*)a >= *(int*)b);
}
