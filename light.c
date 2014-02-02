#include "includes/rtv1.h"

t_light	*new_light(t_vect *p, t_color *c)
{
	t_light	*l;

	l = (t_light*)malloc(sizeof(t_light));
	l->position = p;
	l->color = c;
	return (l);
}

void	delete_light(t_light *l)
{
	delete_vect(l->position);
	delete_color(l->color);
	free(l);
}
