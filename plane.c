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
	if (start == NULL)
			start = new;
	else
	{
		while (start->next != NULL)
				start = start->next;
		start->next = new;
	}
}

t_inter	*findPlanesIntersection(t_ray *ray)
{
	double	mininter;
	double	inter;
	t_vect	*normal;
	t_color	*c;
	t_plane	*p;


	mininter = -1;
	p = get_scene()->planes;
	while (p != NULL)
	{
		inter = findPlaneIntersection(p, ray);
		if (inter > ACCURACY && (inter < mininter || mininter == -1))
		{
			mininter = inter;
			normal = p->normal;
			c = p->color;
		}
		p = p->next;
	}
	return (new_inter(normal, mininter, c));
}

double	findPlaneIntersection(t_plane *p, t_ray *ray)
{
	double	a;
	double	b;

	a = dotProduct(p->normal, ray->direction);
	if (a == 0)
		return (-1);
	else
	{
		b = dotProduct(p->normal, vectAdd(ray->origin,
					negative(vectMult(p->normal, p->distance))));
		return (-b / a);
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
