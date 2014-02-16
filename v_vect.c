/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_vect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:21:16 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 22:09:49 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_vect	*normalize(t_vect *v1)
{
	t_vect	*v2;
	double	m;

	m = magnitude(v1);
	v2 = new_vector(v1->x / m,
					v1->y / m,
					v1->z / m);
	return (v2);
}

t_vect	*negative(t_vect *v1)
{
	t_vect	*v2;

	v2 = new_vector(v1->x * -1, v1->y * -1, v1->z * -1);
	return (v2);
}

t_vect	*crossProduct(t_vect *v1, t_vect *v2)
{
	t_vect	*rslt;

	rslt = new_vector(v1->y * v2->z - v1->z * v2->y,
						v1->z * v2->x - v1->x * v2->z,
						v1->x * v2->y - v1->y * v2->x);
	return (rslt);
}

t_vect	*vect_add(t_vect *v1, t_vect *v2)
{
	t_vect	*rslt;

	rslt = new_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (rslt);
}

t_vect	*vect_mult(t_vect *v1, double scalar)
{
	t_vect	*rslt;

	rslt = new_vector(v1->x * scalar, v1->y * scalar, v1->z * scalar);
	return (rslt);
}
