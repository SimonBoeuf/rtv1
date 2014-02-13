#include "includes/rtv1.h"

double	dotProduct(t_vect *v1, t_vect *v2)
{
	double dotProduct;

	dotProduct = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (dotProduct);
}

double	magnitude(t_vect *v)
{
	return (sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
}
