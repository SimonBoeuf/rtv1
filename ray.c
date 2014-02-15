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
