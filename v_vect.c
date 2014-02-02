#include "includes/rtv1.h"

t_vect	*normalize(t_vect *v1)
{
	t_vect	*v2;

	v2 = new_vector(magnitude(v1) / v1->x, magnitude(v1) / v1->y,
		magnitude(v1) / v1->z);
	return (v2);
}

t_vect	*negative(t_vect *v1)
{
	t_vect *v2;

	v2 = new_vector(-v1->x, -v1->y, -v1->z);
	return (v2);
}

t_vect	*crossProduct(t_vect *v1, t_vect *v2)
{
	t_vect *rslt;

	rslt = new_vector(v1->y * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x);
	return (rslt);
}

t_vect	*vectAdd(t_vect *v1, t_vect *v2)
{
	t_vect *rslt;

	rslt = new_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (rslt);
}

t_vect	*vectMult(t_vect *v1, double scalar)
{
	t_vect *rslt;

	rslt = new_vector(v1->x * scalar, v1->y * scalar, v1->z * scalar);
	return (rslt);
}
