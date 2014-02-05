#include "includes/rtv1.h"

t_scene	*new_scene(void)
{
	t_scene	*s;

	s = (t_scene*)malloc(sizeof(t_scene));
	s->cam = NULL;
	s->lights = NULL;
	s->planes = NULL;
	s->spheres = NULL;
	return (s);
}

void	delete_scene(t_scene *s)
{
	delete_camera(s->cam);
	delete_lights(&s->lights);
	delete_planes(&s->planes);
	delete_spheres(&s->spheres);
	free(s);
}
