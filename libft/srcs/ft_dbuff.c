/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 07:55:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/10 07:40:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"

#define DBUFF_FRONT_AFFINITY 2

/*
** 'ft_dbuff_recenter' recenter zone in buffer.
**				'buf_size' - 'zone_size' should never be lower than 4.
**				'zone_size' should never be 0 when resizing.
*/

// void		ft_dbuff_initzone(t_dbuff *dbuff, size_t rear_pad, DBUFF_T v)
// {
	// return ;
	// dbuff->zone_size = 1;
	// dbuff->zone_rear = dbuff->buf_front + rear_pad;
	// dbuff->zone_front = dbuff->zone_rear;
	// *dbuff->zone_rear = v;
	// return ;
// }

int			ft_dbuff_dup(const t_dbuff *ref, t_dbuff *dst)
{
	ptrdiff_t	diff;

	ft_memcpy(dst, ref, sizeof(t_dbuff));
	dst->buf_rear = (DBUFF_T*)ft_memdup(ref->buf_rear,
			ref->buf_size * sizeof(DBUFF_T));
	if (dst->buf_rear == NULL)
		return (ENOMEM);
	diff = (void*)dst->buf_rear - (void*)ref->buf_rear;
	// dst->buf_rear = (void*)dst->buf_rear + diff;
	dst->buf_front = (void*)dst->buf_front + diff;
	dst->zone_rear = (void*)dst->zone_rear + diff;
	dst->zone_front = (void*)dst->zone_front + diff;
	dst->zone_start = (void*)dst->zone_start + diff;
	
	
	// dst->buf_front += diff;
	// dst->zone_rear += diff;
	// dst->zone_front += diff;
	// dst->zone_start += diff;
	return (0);
}

int			ft_dbuff_init(t_dbuff *dbuff, size_t size, size_t rear_pad)
{
	dbuff->buf_rear = (DBUFF_T*)ft_memalloc(size * sizeof(DBUFF_T));
	if (dbuff->buf_rear == NULL)
		return (ENOMEM);
	dbuff->buf_size = size;
	dbuff->buf_front = dbuff->buf_rear + size - 1;
	dbuff->zone_start = dbuff->buf_rear + rear_pad;
	dbuff->zone_size = 0;
	dbuff->zone_front = NULL;
	dbuff->zone_rear = NULL;
	return (0);
}

int			ft_dbuff_recenter(t_dbuff *dbuff)
{
	ft_memmove(dbuff->zone_start, dbuff->zone_rear,
		dbuff->zone_size * sizeof(DBUFF_T));
	ft_bzero(dbuff->buf_rear, (dbuff->zone_start - dbuff->buf_rear) *
		sizeof(DBUFF_T));
	dbuff->zone_rear = dbuff->zone_start;
	dbuff->zone_front = dbuff->zone_rear + dbuff->zone_size - 1;
	ft_bzero(dbuff->zone_front + 1, (dbuff->buf_front - dbuff->zone_front) *
		sizeof(DBUFF_T));
	return (0);
}
