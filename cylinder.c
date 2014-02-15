#include "includes/rtv1.h"

t_cylinder	*new_cylinder(t_vect *center, double radius, t_color *color)
{
	t_cylinder	*c;

	c = (t_cylinder*)malloc(sizeof(t_cylinder));
	c->center = center;
	c->radius = radius;
	c->color = color;
	return (c);
}

void		add_cylinder(t_cylinder *start, t_cylinder *new)
{
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}

void		delete_cylinders(t_cylinder **start)
{
	t_cylinder *tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		delete_vect((*start)->center);
		delete_color((*start)->color);
		(*start)->next = NULL;
		free(*start);
		*start = tmp;
	}
}
