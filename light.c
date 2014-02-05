#include "includes/rtv1.h"

t_light	*new_light(t_vect *p, t_color *c)
{
	t_light	*l;

	l = (t_light*)malloc(sizeof(t_light));
	l->position = p;
	l->color = c;
	l->next = NULL;
	return (l);
}

void	add_light(t_light *start, t_light *new)
{
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}

void	delete_lights(t_light **start)
{
	t_light	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		delete_vect((*start)->position);
		delete_color((*start)->color);
		(*start)->next = NULL;
		free(*start);
		*start = tmp;
	}
}
