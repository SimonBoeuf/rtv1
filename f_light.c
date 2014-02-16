/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:02 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:18:03 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

t_light	*get_spots(int fd)
{
	int			r;
	char		*line;
	t_light		*l;

	l = NULL;
	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("new:", line))
		{
			if (l == NULL)
				l = get_spot(fd);
			else
				add_light(l, get_spot(fd));
		}
	}
	if (r == -1)
			exit (-1);
	return (l);
}

t_light	*get_spot(int fd)
{
	int			r;
	char		*line;
	t_vect		*pos;
	t_color		*color;

	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("pos:", line))
			pos = get_vector(fd);
		if (!ft_strcmp("color:", line))
			color = get_color(fd);
	}
	if (r == -1)
			exit(-1);
	return (new_light(pos, color));
}
