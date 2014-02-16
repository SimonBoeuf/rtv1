/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/30 17:58:47 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:23:21 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_color	*new_color(double red, double green, double blue, double special)
{
	t_color	*c;

	c = (t_color*)malloc(sizeof(t_color));
	c->red = red;
	c->green = green;
	c->blue = blue;
	c->spec = special;
	return (c);
}

void	delete_color(t_color *c)
{
	free(c);
}

t_color	*cpy_color(t_color *c)
{
	return (new_color(c->red, c->green, c->blue, c->spec));
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

int		get_color_number(t_color *c)
{
	int	rslt;

	rslt = c->red * 255;
	rslt = rslt << 8;
	rslt += c->green * 255;
	rslt = rslt << 8;
	rslt += c->blue * 255;
	return (rslt);
}
