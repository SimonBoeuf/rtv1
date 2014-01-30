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

# include "rtv1.h"

t_color	*new_color(void)
{
	t_color	*c;

	c = (t_color*)malloc(sizeof(t_color));
	c->red = 0;
	c->green = 0;
	c->blue = 0;
	c->special = 0;
	return (c);
}

double	brightness(t_color *c)
{
	return ((c->red + c->green + c->blue) / 3);
}

t_color	*colorScalar(double scalar, t_color *c1)
{
	t_color	*c2;

	c2 = new_color();
	c2->red = c1->red *scalar;
}
