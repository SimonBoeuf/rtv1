#include "includes/rtv1.h"

t_vect	*new_vector(double x, double y, double z)
{
	t_vect	*v;

	v = (t_vect*)malloc(sizeof(t_vect));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

void	delete_vect(t_vect *v)
{
	free(v);
}
