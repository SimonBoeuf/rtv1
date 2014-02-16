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
	float		a;
	t_vect		*dist_l;
	t_ray		*shadow;
	t_color		*f;

	f = colorScalar(AMBIENTLIGHT, c);
	l = get_scene()->lights;
	while (l != NULL)
	{
		dist_l = normalize(vectAdd(l->position, negative(r->origin)));
		a = dotProduct(n, dist_l);
		shadow = new_ray(r->origin, dist_l);
		if (a > 0 && find_min_inter(shadow)->dist <= ACCURACY)
		{
				f = colorAdd(f, colorScalar(a, colorMultiply(c, l->color)));
				if (c->special > 0 && c->special <= 1)
					f = colorAdd(f, colorScalar(pow(dotProduct(get_ref_ray(n, r)->direction, dist_l), 100) * c->special, l->color));
		}
		l = l->next;
	}
	return (f);
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

