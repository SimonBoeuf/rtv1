/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:10 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 21:37:53 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_vect		*getNormalAtCone(t_cone *cone, t_vect *point)
{
	t_vect	*v;

	v = normalize(vectAdd(point, negative(cone->center)));
	return (v);
}

t_inter		*findConesIntersection(t_ray *ray)
{
	double		mininter;
	double		inter;
	t_vect		*normal;
	t_color		*c;
	t_cone		*cone;

	mininter = -1;
	cone = get_scene()->cones;
	while (cone != NULL)
	{
		inter = findConeIntersection(cone, ray);
		if (inter > ACCURACY && (inter < mininter || mininter == -1))
		{
			mininter = inter;
			normal = getNormalAtCone(cone, vectAdd(ray->origin,
									vectMult(ray->direction, inter)));
			c = cone->color;
		}
		cone = cone->next;
	}
	return (new_inter(normal, mininter, c));
}

double		findConeIntersection(t_cone *cone, t_ray *r)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt;

	a = pow(cos(cone->alpha), 2) *
		pow((r->direction->x + r->direction->z), 2) -
		pow(sin(cone->alpha), 2) *
		pow(r->direction->y, 2);
	b = 2 * pow(cos(cone->alpha), 2) *
		(r->direction->x * (r->origin->x - cone->center->x) + 
			r->direction->z * (r->origin->z - cone->center->z)) -
		2 * pow(sin(cone->alpha), 2) *
		r->direction->y * (r->origin->y - cone->center->y);
	c = pow(cos(cone->alpha), 2) *
		pow(r->origin->x - cone->center->x + r->origin->z - cone->center->z, 2) -
		pow(sin(cone->alpha), 2) *
		pow(r->origin->y - cone->center->y, 2);
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

t_cone	*get_cones(int fd)
{
	int			r;
	char		*line;
	t_cone		*c;

	c = NULL;
	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("new:", line))
		{
			if (c == NULL)
				c = get_cone(fd);
			else
				add_cone(c, get_cone(fd));
		}
	}
	if (r == -1)
		exit (-1);
	return (c);
}

t_cone		*get_cone(int fd)
{
	int			r;
	char		*line;
	t_vect		*center;
	double		alpha;
	t_color		*color;

	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("pos:", line))
			center = get_vector(fd);
		if (!ft_strcmp("alpha:", line))
		{
			r = get_next_line(fd, &line);
			alpha = ft_atodouble(&line);
		}
		if (!ft_strcmp("color:", line))
			color = get_color(fd);
	}
	if (r == -1)
			exit(-1);
	return (new_cone(center, alpha, color));
}
