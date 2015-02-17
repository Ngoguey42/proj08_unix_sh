/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 06:46:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 10:43:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "ft_math.h"
#include "libft.h"

int			ft_dstor_dup(const t_dstor *ref, t_dstor *dst)
{
	ptrdiff_t	diff;

	ft_memcpy(dst, ref, sizeof(t_dstor));
	dst->buf_rear = (DSTOR_T*)ft_memdup(ref->buf_rear,
			ref->buf_size * sizeof(DSTOR_T));
	if (dst->buf_rear == NULL)
		return (ENOMEM);
	diff = (void*)dst->buf_rear - (void*)ref->buf_rear;
	dst->zone_front += diff;
	return (0);
}

int			ft_dstor_init(t_dstor *dstor, size_t size)
{
	dstor->buf_rear = (DSTOR_T*)ft_memalloc(size * sizeof(DSTOR_T));
	if (dstor->buf_rear == NULL)
		return (ENOMEM);
	dstor->buf_size = size;
	dstor->zone_front = NULL;
	dstor->zone_size = 0;
	return (0);
}

int			ft_dstor_realloc(t_dstor *dstor, size_t new_size)
{
	DSTOR_T	*buf_new;

	buf_new = (DSTOR_T*)malloc(new_size * sizeof(DSTOR_T));
	if (buf_new == NULL)
		return (ENOMEM);
	dstor->zone_size = MIN(new_size, dstor->zone_size);
	(void)ft_memcpy(buf_new, dstor->buf_rear, dstor->zone_size);
	free(dstor->buf_rear);
	dstor->buf_rear = buf_new;
	dstor->buf_size = new_size;
	if (dstor->zone_size == 0)
		dstor->zone_front = NULL;
	else
	{
		dstor->zone_front = dstor->buf_rear + dstor->zone_size - 1;
		(void)ft_bzero(dstor->zone_front + 1, new_size - dstor->zone_size);
	}
	return (0);
}
