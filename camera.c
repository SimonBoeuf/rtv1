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
