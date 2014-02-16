/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:05 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:18:07 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_plane	*get_planes(int fd)
{
	int			r;
	char		*line;
	t_plane		*p;

	p = NULL;
	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("new:", line))
		{
			if (p == NULL)
				p = get_plane(fd);
			else
				add_plane(p, get_plane(fd));
		}
	}
	if (r == -1)
			exit (-1);
	return (p);
}

t_plane	*get_plane(int fd)
{
	int			r;
	char		*line;
	t_vect		*normal;
	double		distance;
	t_color		*color;

	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("pos:", line))
			normal = get_vector(fd);
		if (!ft_strcmp("dist:", line))
		{
			r = get_next_line(fd, &line);
			distance = ft_atodouble(&line);
		}
		if (!ft_strcmp("color:", line))
			color = get_color(fd);
	}
	if (r == -1)
			exit(-1);
	return (new_plane(normal, distance, color));
}
