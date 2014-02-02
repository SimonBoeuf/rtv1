#include "includes/rtv1.h"

double	brightness(t_color *c)
{
	return ((c->red + c->green + c->blue) / 3);
}

t_color	*colorScalar(double scalar, t_color *c1)
{
	t_color	*c2;

	c2 = new_color(c1->red * scalar,c1->green * scalar,
		c1->blue *scalar, c1->special);
	return (c2);
}

t_color	*colorAdd(t_color *c1, t_color *c2)
{
	t_color	*rslt;

	rslt = new_color(c1->red + c2->red, c1->green + c2->green,
		c1->blue + c2->blue, c1->special);
	return (rslt);
}

t_color	*colorMultiply(t_color *c1, t_color *c2)
{
	t_color	*rslt;

	rslt = new_color(c1->red * c2->red, c1->green * c2->green,
		c1->blue * c2->blue, c1->special);
	return (rslt);
}

