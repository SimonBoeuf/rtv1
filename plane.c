/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:20:54 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 22:18:42 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_inter	*find_planes_intersection(t_ray *ray)
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
		inter = find_plane_intersection(p, ray);
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

double	find_plane_intersection(t_plane *p, t_ray *ray)
{
	double	a;
	double	b;

	a = dot_product(p->normal, ray->direction);
	if (a == 0)
		return (-1);
	else
	{
		b = dot_product(p->normal, vect_add(ray->origin,
					negative(vect_mult(p->normal, p->distance))));
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
