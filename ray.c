/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:21:04 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:21:06 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_ray	*new_ray(t_vect *o, t_vect *d)
{
	t_ray	*r;

	r = (t_ray*)malloc(sizeof(t_ray));
	r->origin = o;
	r->direction = d;
	return (r);
}

t_ray	*cpy_ray(t_ray *r)
{
	return (new_ray(r->origin, r->direction));
}

void	delete_ray(t_ray *r)
{
	delete_vect(r->origin);
	delete_vect(r->direction);
	free(r);
}
