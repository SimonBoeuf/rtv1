#include "includes/rtv1.h"

t_ray	*get_intersection_ray(t_ray *r, double inter)
{
	t_vect	*v;
	t_ray	*rslt;

	v = vectMult(r->direction, inter);
	v = vectAdd(r->origin, v);
	rslt = new_ray(cpy_vect(v), cpy_vect(r->direction));
	return (rslt);
}

t_ray	*get_ref_ray(t_vect *n, t_ray *r)
{
	t_ray	*ref_ray;
	t_vect	*scalar1;
	t_vect	*scalar2;
	t_vect	*add1;
	t_vect	*add2;

	scalar1 = negative(r->direction);
	scalar1 = vectMult(n, dotProduct(n, scalar1));
	add1 = vectAdd(scalar1, r->direction);
	scalar2 = vectMult(add1, 2);
	scalar1 = negative(r->direction);
	add2 = vectAdd(scalar1, scalar2);
	scalar1 = normalize(add2);
	ref_ray = new_ray(cpy_vect(r->origin), cpy_vect(scalar1));
	return (ref_ray);
}

t_ray	*get_ray(t_camera *c, double x, double y)
{
	t_vect	*v1;
	t_vect	*v2;
	t_ray	*rslt;

	v1 = vectMult(c->camright, x - 0.5);
	v2 = vectMult(c->camdown, y - 0.5);
	v1 = vectAdd(v1, v2);
	v1 = vectAdd(c->camdir, v1);
	v1 = normalize(v1);

	rslt = new_ray(c->campos, v1);
	return (rslt);
}
