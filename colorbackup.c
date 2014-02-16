/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorbackup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:17:44 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:17:46 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/rtv1.h"

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
		if (min->c->special > 0 && min->c->special <= 1)
			rslt = reflection(min->c, ref_inter_ray, min->normal);
		else if (min->c->special >= 2)
			rslt = square_plane(c, ref_inter_ray, normal);
		else
			rslt = c;
		rslt = colorAdd(c, colorScalar(rslt->special, rslt));
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
		rslt = reflection(new_color(0, 0, 0, c->special), iray, n);
	else
		rslt = reflection(c, iray, n);
	return (rslt);
}

t_color	*correct_light(t_color *c, t_ray *r, t_vect *n)
{
	t_light		*l;
	float		cosine_angle;
	t_vect		*dist_l;
	t_vect		*ref_dir;
	double		specular;

	c = colorScalar(AMBIENTLIGHT, c);
	l = get_scene()->lights;
	while (l != NULL)
	{
		dist_l = normalize(vectAdd(l->position, negative(r->origin)));
		cosine_angle = dotProduct(n, dist_l);
		if (cosine_angle > 0 && find_min_inter(new_ray(r->origin, dist_l))->dist <= ACCURACY)
		{
				c = colorAdd(c, colorScalar(cosine_angle, colorMultiply(c, l->color)));
				ref_dir = get_ref_ray(n, r)->direction;
				specular = pow(dotProduct(ref_dir, dist_l), 1);
				if (specular > 0)
					c = colorAdd(c, colorScalar(specular * c->special, l->color));
		}
		l = l->next;
	}
	return (c);
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_ray	*iray;

	iray = get_intersection_ray(ray, inter);
	if (c->special >= 2)
		c = square_plane(c, iray, normal);
	if (c->special > 0 && c->special <= 1)
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

