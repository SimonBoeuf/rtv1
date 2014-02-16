/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:21:14 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:49:57 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_sphere	*new_sphere(t_vect *center, double radius, t_color *color)
{
	t_sphere	*s;

	s = (t_sphere*)malloc(sizeof(t_sphere));
	s->center = center;
	s->radius = radius;
	s->color = color;
	return (s);
}

void		add_sphere(t_sphere *start, t_sphere *new)
{
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}

void		delete_spheres(t_sphere **start)
{
	t_sphere	*tmp;

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
