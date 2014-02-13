#include "includes/rtv1.h"

t_camera	*new_camera(t_vect *p, t_vect *di, t_vect *r, t_vect *dwn)
{
	t_camera	*c;

	c = (t_camera*)malloc(sizeof(t_camera));
	c->campos = p;
	c->camdir = di;
	c->camright = r;
	c->camdown = dwn;
	return (c);
}

void		delete_camera(t_camera *c)
{
	delete_vect(c->campos);
	delete_vect(c->camdir);
	delete_vect(c->camright);
	delete_vect(c->camdown);
	free(c);
}

t_camera	*get_camera(int fd)
{
	int			r;
	t_camera	*c;
	char		*line;
	t_vect		*diff_btw;
	t_vect		*look_at;

	c = new_camera(NULL, NULL, NULL, NULL);
	while ((r = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "----------"))
	{
		if (!ft_strcmp("pos:", line))
				c->campos = get_vector(fd);
		if (!ft_strcmp("dir:", line))
				look_at = get_vector(fd);
	}
	if (r == -1)
			exit(-1);
	diff_btw = new_vector(c->campos->x - look_at->x,
							c->campos->y - look_at->y,
							c->campos->z - look_at->z);
	c->camdir = normalize(negative(diff_btw));
	c->camright = normalize(crossProduct(new_vector(0, 1, 0), c->camdir));
	c->camdown = crossProduct(c->camright, c->camdir);
	return (c);
}
