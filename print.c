#include "includes/rtv1.h"
#include <stdio.h>

void	print_scene(t_scene *s)
{
	t_light		*tmpl;
	t_sphere	*tmps;
	t_plane		*tmpp;
	int			i;

	ft_putendl("scene :\ncamera :");
	print_camera(s->cam);
	ft_putendl("lights :");
	i = 0;
	tmpl = s->lights;
	while (tmpl != NULL)
	{
		printf("%d", ++i);
		print_light(tmpl);
		tmpl = tmpl->next;
	}
	ft_putendl("planes :");
	i = 0;
	tmpp = s->planes;
	while (tmpp != NULL)
	{
		printf("%d", ++i);
		print_plane(tmpp);
		tmpp = tmpp->next;
	}
	ft_putendl("\nspheres :");
	i = 0;
	tmps = s->spheres;
	while (tmps != NULL)
	{
		printf("%d", ++i);
		print_sphere(tmps);
		tmps = tmps->next;
	}
}

void	print_camera(t_camera *c)
{
	ft_putendl("campos :");
	print_vect(c->campos);
	ft_putendl("camdir :");
	print_vect(c->camdir);
	ft_putendl("camright :");
	print_vect(c->camright);
	ft_putendl("camdown :");
	print_vect(c->camdown);
}

void	print_light(t_light *l)
{
	ft_putendl("position :");
	print_vect(l->position);
	ft_putendl("color :");
	print_color(l->color);
}

void	print_plane(t_plane *p)
{
	ft_putendl("normal :");
	print_vect(p->normal);
	printf("distance : %f\n", p->distance);
	ft_putendl("color ");
	print_color(p->color);
}

void	print_sphere(t_sphere *s)
{
	ft_putendl("center :");
	print_vect(s->center);
	printf("radius : %f\n", s->radius);
	ft_putendl("color ");
	print_color(s->color);
}

void	print_vect(t_vect *v)
{
	printf("x : %f\ny : %f\nz : %f\n", v->x, v->y, v->z);
}

void	print_color(t_color *c)
{
	printf("red : %f\ngreen : %f\nblue : %f\nspecial : %f\n", c->red, c->green, c->blue, c->special);
}
