/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:00 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 21:42:56 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_vect		*getNormalAtCylinder(t_cylinder *c, t_vect *point)
{
	t_vect	*v;

	v = normalize(vectAdd(new_vector(point->x, 0, point->z),
				negative(new_vector(c->center->x, 0, c->center->z))));
	return (v);
}

t_inter		*findCylindersIntersection(t_ray *ray)
{
	double		mininter;
	double		inter;
	t_vect		*normal;
	t_color		*color;
	t_cylinder	*c;

	mininter = -1;
	c = get_scene()->cylinders;
	while (c != NULL)
	{
		inter = findCylinderIntersection(c, ray);
		if (inter > ACCURACY && (inter < mininter || mininter == -1))
		{
			mininter = inter;
			normal = getNormalAtCylinder(c, vectAdd(ray->origin,
									vectMult(ray->direction, inter)));
			color = c->color;
		}
		c = c->next;
	}
	return (new_inter(normal, mininter, color));
}

double		findCylinderIntersection(t_cylinder *cy, t_ray *r)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt;

	a = pow(r->direction->x, 2) +
		pow(r->direction->z, 2);
	b = (2 * (r->direction->x * (r->origin->x - cy->center->x))) +
		(2 * (r->direction->z * (r->origin->z - cy->center->z)));
	c = pow(r->origin->x - cy->center->x, 2) +
		pow(r->origin->z - cy->center->z, 2) -
		cy->radius * cy->radius;
	d = b * b - 4 * a * c;
	if (d > 0)
	{
		rslt = ((-b - sqrt(d)) / (2 * a)) - 0.000001 > 0 ?
			(-b - sqrt(d)) / (2 * a) - 0.000001 :
			(-b + sqrt(d)) / (2 * a) - 0.000001;
	}
	else
		rslt = -1;
	return (rslt);
}

t_cylinder	*get_cylinders(int fd)
{
	int			r;
	char		*line;
	t_cylinder	*c;

	c = NULL;
	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("new:", line))
		{
			if (c == NULL)
				c = get_cylinder(fd);
			else
				add_cylinder(c, get_cylinder(fd));
		}
	}
	if (r == -1)
		exit(-1);
	return (c);
}

t_cylinder	*get_cylinder(int fd)
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
	return (new_cylinder(center, radius, color));
}
