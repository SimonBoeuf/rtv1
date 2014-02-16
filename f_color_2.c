/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_color_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:17:57 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 22:11:25 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_color	*reflection(t_color *c, t_ray *r, t_vect *normal)
{
	t_ray		*ref;
	t_inter		*min;
	t_color		*rslt;
	t_ray		*ref_inter_ray;

	ref = get_ref_ray(normal, r);
	min = find_min_inter(ref);
	if (min->dist > ACCURACY)
	{
		ref_inter_ray = get_intersection_ray(ref, min->dist);
		if (min->c->spec > 0 && min->c->spec <= 1)
			rslt = reflection(min->c, ref_inter_ray, min->normal);
		else if (min->c->spec >= 2)
			rslt = square_plane(c, ref_inter_ray, normal);
		else
			rslt = c;
		rslt = color_add(c, color_scalar(rslt->spec, rslt));
	}
	else
		rslt = c;
	return (rslt);
}

t_color	*square_plane(t_color *c, t_ray *iray, t_vect *n)
{
	int		square;
	t_color	*rslt;

	square = (int)floor(iray->origin->x) + (int)floor(iray->origin->z);
	if (square % 2 == 0)
		rslt = reflection(new_color(0, 0, 0, c->spec), iray, n);
	else
		rslt = reflection(c, iray, n);
	return (rslt);
}

t_color	*correct_light(t_color *c, t_ray *r, t_vect *n)
{
	t_light		*l;
	float		a;
	t_vect		*dist_l;
	t_ray		*shadow;
	t_color		*f;

	f = color_scalar(AMBIENTLIGHT, c);
	l = get_scene()->lights;
	while (l != NULL)
	{
		dist_l = normalize(vect_add(l->position, negative(r->origin)));
		a = dot_product(n, dist_l);
		shadow = new_ray(r->origin, dist_l);
		if (a > 0 && find_min_inter(shadow)->dist <= ACCURACY)
		{
				f = color_add(f, color_scalar(a, color_multiply(c, l->c)));
				if (c->spec > 0 && c->spec <= 1)
				{
					a = dot_product(get_ref_ray(n, r)->direction, dist_l);
					f = color_add(f, color_scalar(pow(a, 100) * c->spec, l->c));
				}
		}
		l = l->next;
	}
	return (f);
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_ray	*iray;

	iray = get_intersection_ray(ray, inter);
	if (c->spec >= 2)
		c = square_plane(c, iray, normal);
	if (c->spec > 0 && c->spec <= 1)
		c = reflection(c, iray, normal);
	c = correct_light(c, iray, normal);
	return (clip(c));
}

t_color	*get_object_color(t_ray *ray)
{
	t_color		*rslt;
	t_inter		*mininter;

	mininter = find_min_inter(ray);
	if (mininter->dist > ACCURACY)
		rslt = correct(mininter->c, ray, mininter->normal, mininter->dist);
	else
		rslt = new_color(0, 0, 0, 0);
	return (rslt);
}

