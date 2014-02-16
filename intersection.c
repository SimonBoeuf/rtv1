/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 15:07:00 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 16:57:22 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_inter		*new_inter(t_vect *n, double dist, t_color *c)
{
	t_inter	*i;

	i = (t_inter*)malloc(sizeof(t_inter));
	i->normal = n;
	i->dist = dist;
	i->c = c;

	return (i);
}

t_inter		*min_inter(t_inter *i, t_inter *i2)
{
	if (i2 == NULL)
		return (i);
	if (i == NULL)
		return (i2);
	if ((i2->dist < i->dist || i->dist == -1) && i2->dist > ACCURACY)
		return (i2);
	return (i);
}
