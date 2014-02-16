/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:10 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:44:25 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_vect		*get_normal_at_sphere(t_sphere *sphere, t_vect *point)
{
	t_vect	*v;

	v = normalize(vect_add(point, negative(sphere->center)));
	return (v);
}

t_inter		*find_spheres_intersection(t_ray *ray)
{
	double		mininter;
	double		inter;
	t_vect		*normal;
	t_color		*c;
	t_sphere	*s;

	mininter = -1;
	s = get_scene()->spheres;
	while (s != NULL)
	{
		inter = find_sphere_intersection(s, ray);
		if (inter > ACCURACY && (inter < mininter || mininter == -1))
		{
			mininter = inter;
			normal = get_normal_at_sphere(s, vect_add(ray->origin,
									vect_mult(ray->direction, inter)));
			c = s->color;
		}
		s = s->next;
	}
	return (new_inter(normal, mininter, c));
}

double		find_sphere_intersection(t_sphere *s, t_ray *r)
{
	double	b;
	double	c;
	double	d;
	double	rslt;

	b = (2 * (r->origin->x - s->center->x) * r->direction->x) +
		(2 * (r->origin->y - s->center->y) * r->direction->y) +
		(2 * (r->origin->z - s->center->z) * r->direction->z);
	c = pow(r->origin->x - s->center->x, 2) +
		pow(r->origin->y - s->center->y, 2) +
		pow(r->origin->z - s->center->z, 2) - (s->radius * s->radius);
	d = b * b - 4 * c;
	if (d > 0)
	{
		rslt = ((-b - sqrt(d)) / 2) - 0.000001 > 0 ?
			(-b - sqrt(d)) / 2 - 0.000001 :
			(-b + sqrt(d)) / 2 - 0.000001;
	}
	else
		rslt = -1;
	return (rslt);
}

t_sphere	*get_spheres(int fd)
{
	int			r;
	char		*line;
	t_sphere	*s;

	s = NULL;
	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("new:", line))
		{
			if (s == NULL)
				s = get_sphere(fd);
			else
				add_sphere(s, get_sphere(fd));
		}
	}
	if (r == -1)
		exit (-1);
	return (s);
}

t_sphere	*get_sphere(int fd)
{
	int			r;
	char		*line;
	t_vect		*center;
	double		radius;
	t_color		*color;

	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("pos:", line))
			center = get_vector(fd);
		if (!ft_strcmp("radius:", line))
		{
			r = get_next_line(fd, &line);
			radius = ft_atodouble(&line);
		}
		if (!ft_strcmp("color:", line))
			color = get_color(fd);
	}
	if (r == -1)
			exit(-1);
	return (new_sphere(center, radius, color));
}
