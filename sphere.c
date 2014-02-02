#include "includes/rtv1.h"

t_sphere	*new_sphere(t_vect *center, double radius, t_color *color)
{
	t_sphere	*s;

	s = (t_sphere*)malloc(sizeof(t_sphere));
	s->center = center;
	s->radius = radius;
	s->color = color;
	return (s);
}

t_vect		*getNormalAtSphere(t_sphere *sphere, t_vect *point)
{
	t_vect	*v;
	v = vectAdd(point, negative(normalize(sphere->center)));
	return (v);
}

double		findSphereIntersection(t_sphere *s, t_ray *r)
{
	double	b;
	double	c;
	double	d;
	double	rslt;

	b = (2 * (r->origin->x - s->center->x) * r->direction->x) + 
		(2 * (r->origin->y - s->center->y) * r->direction->y)
		+ (2 * (r->origin->z - s->center->z) * r->direction->z);
	c = pow(r->origin->x - s->center->x, 2) +
		pow(r->origin->y - s->center->y, 2) +
		pow(r->origin->z - s->center->z, 2) - s->radius * s->radius;
	d = b * b - 4 * c;
	if (d > 0)
	{
		rslt = (-b - sqrt(d / 2) - 0.000001) > 0 ?
			-b - sqrt(d / 2) - 0.000001 :
			-b + sqrt(d / 2) - 0.000001;
	}
	else
		rslt = -1;
	return (rslt);
}

void	delete_sphere(t_sphere *s)
{
	delete_vect(s->center);
	delete_color(s->color);
	free(s);
}
