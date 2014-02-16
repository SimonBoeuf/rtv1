/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:20:42 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:22:49 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_light	*new_light(t_vect *p, t_color *c)
{
	t_light	*l;

	l = (t_light*)malloc(sizeof(t_light));
	l->position = p;
	l->c = c;
	l->next = NULL;
	return (l);
}

void	add_light(t_light *start, t_light *new)
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

void	delete_lights(t_light **start)
{
	t_light	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		delete_vect((*start)->position);
		delete_color((*start)->c);
		(*start)->next = NULL;
		free(*start);
		*start = tmp;
	}
}
