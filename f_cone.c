/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:10 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 22:47:26 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_vect		*get_normal_at_cone(t_cone *cone, t_vect *point)
{
	t_vect	*v;

	v = normalize(vect_add(point, negative(cone->center)));
	return (v);
}

t_inter		*find_cones_intersection(t_ray *ray)
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
		inter = find_cone_intersection(cone, ray);
		if (inter > ACCURACY && (inter < mininter || mininter == -1))
		{
			mininter = inter;
			normal = get_normal_at_cone(cone, vect_add(ray->origin,
									vect_mult(ray->direction, inter)));
			c = cone->color;
		}
		cone = cone->next;
	}
	return (new_inter(normal, mininter, c));
}

double		find_cone_intersection(t_cone *cone, t_ray *r)
{
	(void)cone;
	(void)r;
	return (-1);
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
