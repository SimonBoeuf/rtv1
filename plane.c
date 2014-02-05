#include "includes/rtv1.h"

t_plane	*new_plane(t_vect *normal, double distance, t_color *c)
{
	t_plane	*p;

	p = (t_plane*)malloc(sizeof(t_plane));
	p->normal = normal;
	p->distance = distance;
	p->color = c;
	p->next = NULL;
	return (p);
}

void	add_plane(t_plane *start, t_plane *new)
{
	while (start->next != NULL)
			start = start->next;
	start->next = new;
}

double	findPlaneIntersection(t_plane *p, t_ray *ray)
{
	double	a;
	double	b;

	a = dotProduct(ray->direction, p->normal);
	if (a == 0)
		return (-1);
	else
	{
		b = dotProduct(p->normal, vectAdd(ray->origin, negative(
					vectMult(p->normal, p->distance))));
		return (-1 * b / a);
	}
}

void	delete_planes(t_plane **start)
{
	t_plane	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		delete_vect((*start)->normal);
		delete_color((*start)->color);
		(*start)->next = NULL;
		free(*start);
		*start = tmp;
	}
}
