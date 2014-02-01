/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/30 17:58:47 by sboeuf            #+#    #+#             */
/*   Updated: 2014/01/30 18:07:34 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/rtv1.h"

t_color	*new_color(double red, double green, double blue, double special)
{
	t_color	*c;

	c = (t_color*)malloc(sizeof(t_color));
	c->red = red;
	c->green = green;
	c->blue = blue;
	c->special = special;
	return (c);
}

void	delete_color(t_color *c)
{
	free(c);
}
