/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nextval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 08:50:34 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/28 08:52:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

double		ft_nextval(double val, double direction)
{
	if (direction > 0)
		return (floor(val) + 1.);
	else if (direction < 0)
		return (ceil(val) - 1.);
	return (val);
}
