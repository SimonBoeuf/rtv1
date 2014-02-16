/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:17:47 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 21:02:25 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_cone		*new_cone(t_vect *center, double alpha, t_color *color)
{
	t_cone	*c;

	c = (t_cone*)malloc(sizeof(t_cone));
	c->center = center;
	c->alpha = alpha;
	c->color = color;
	return (c);
}

void		add_cone(t_cone *start, t_cone *new)
{
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}

void		delete_cones(t_cone **start)
{
	t_cone	*tmp;

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
