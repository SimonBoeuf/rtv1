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
				add_light(l, get_spot(fd));
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
