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

double	brightness(t_color *c)
{
	return ((c->red + c->green + c->blue) / 3);
}

t_color	*get_color(int fd)
{
	double	r;
	double	g;
	double	b;
	double	s;
	char	*line;

	if (get_next_line(fd, &line) < 1)
			exit(-1);
	r = ft_atodouble(&line);
	g = ft_atodouble(&line);
	b = ft_atodouble(&line);
	s = ft_atodouble(&line);
	return (new_color(r, g, b, s));
}
