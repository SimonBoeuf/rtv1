#include "includes/rtv1.h"

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

t_color	*colorAverage(t_color *c1, t_color *c2)
{
	t_color	*r;

	r = new_color((c1->red + c2->red) / 2, (c1->green + c2->green) / 2,
				   (c1->blue * c2->blue) / 2, c1->special);
	return (r);
}

t_color	*clip(t_color *c1)
{
	double	all_light;
	double	excess_light;

	all_light = c1->red + c1->green + c1->blue;
	excess_light = all_light - 3;
	if (excess_light > 0)
	{
		c1->red = c1->red + excess_light * (c1->red / all_light);
		c1->green = c1->green + excess_light * (c1->green / all_light);
		c1->blue = c1->blue + excess_light * (c1->blue / all_light);
	}
	c1->red = c1->red < 0 ? 0 : c1->red > 1 ? 1 : c1->red;
	c1->green = c1->green < 0 ? 0 : c1->green > 1 ? 1 : c1->green;
	c1->blue = c1->blue < 0 ? 0 : c1->blue > 1 ? 1 : c1->blue;
	return (new_color(c1->red, c1->green, c1->blue, c1->special));
}
