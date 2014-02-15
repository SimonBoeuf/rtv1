#include "includes/rtv1.h"
#include <stdio.h>

t_color	*square_plane(t_color *c, t_ray *iray)
{
	int		square;
	t_color	*rslt;

	square = (int)floor(iray->origin->x) + (int)floor(iray->origin->z);
	if (square % 2 == 0)
		rslt = new_color(0, 0, 0, c->special);
	else
		rslt = new_color(c->red, c->green, c->blue, c->special);
	return (rslt);
}

t_ray	*get_ref_ray(t_vect *n, t_ray *r)
{
	t_ray	*ref_ray;
	t_vect	*scalar1;
	t_vect	*scalar2;
	t_vect	*add1;
	t_vect	*add2;

	scalar1 = negative(r->direction);
	scalar1 = vectMult(n, dotProduct(n, scalar1));
	add1 = vectAdd(scalar1, r->direction);
	scalar2 = vectMult(add1, 2);
	scalar1 = negative(r->direction);
	add2 = vectAdd(scalar1, scalar2);
	scalar1 = normalize(add2);
	ref_ray = new_ray(cpy_vect(r->origin), cpy_vect(scalar1));
	return (ref_ray);
}

t_color	*correct_light(t_color *c, t_ray *r, t_vect *n)
{
	t_light		*l;
	float		cosine_angle;
	t_vect		*dist_l;
	t_ray		*shadow;
	int			shadowed;
	t_color		*rslt;
	t_vect		*ref_dir;
	double		specular;

	rslt = colorScalar(AMBIENTLIGHT, c);
	l = get_scene()->lights;
	while (l != NULL)
	{
		dist_l = normalize(vectAdd(l->position, negative(r->origin)));
		cosine_angle = dotProduct(n, dist_l);
		if (cosine_angle > 0)
		{
			shadow = new_ray(r->origin, dist_l);
			shadowed = 0;
			if (findSpheresIntersection(shadow)->radius > ACCURACY || findPlanesIntersection(shadow)->distance > ACCURACY)
				shadowed = 1;
			if (!shadowed)
			{
				rslt = colorAdd(rslt, colorScalar(cosine_angle, colorMultiply(c,
												l->color)));
				if (c->special > 0 && c->special <= 1)
				{
					ref_dir = get_ref_ray(n, r)->direction;
					specular = dotProduct(ref_dir, dist_l);
					if (specular > 0)
					{
						specular = pow(specular, 100);
						rslt = colorAdd(rslt, colorScalar(specular * c->special, l->color));
					}
				}
			}
		}
		l = l->next;
	}
	return (rslt);
}

t_ray	*get_intersection_ray(t_ray *r, double inter)
{
	t_vect	*v;
	t_ray	*rslt;

	v = vectMult(r->direction, inter);
	v = vectAdd(r->origin, v);
	rslt = new_ray(cpy_vect(v), cpy_vect(r->direction));
	return (rslt);
}

t_color	*reflection(t_color *c, t_ray *r, t_vect *normal)
{
	t_ray		*ref;
	t_sphere	*s;
	t_plane		*p;
	t_color		*rslt;
	t_ray		*ref_inter_ray;

	ref = get_ref_ray(normal, r);
	s = findSpheresIntersection(ref);
	p = findPlanesIntersection(ref);
	if ((s->radius < p->distance || p->distance == -1) && s->radius > ACCURACY)
	{
		ref_inter_ray = get_intersection_ray(ref, s->radius);
		if (s->color->special > 0 && s->color->special <= 1)
			rslt = reflection(s->color, ref_inter_ray, s->center);
		else
			rslt = c;
		rslt = colorAdd(c, colorScalar(rslt->special, rslt));
	}
	else if ((p->distance <= s->radius || s->radius == -1) && p->distance > ACCURACY)
	{
		ref_inter_ray = get_intersection_ray(ref, p->distance);
		rslt = square_plane(c, ref_inter_ray);
		rslt = colorAdd(c, colorScalar(rslt->special, rslt));
	}
	else
		rslt = c;
	return (rslt);
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_ray	*iray;

	iray = get_intersection_ray(ray, inter);
	if (c->special == 2)
		c = square_plane(c, iray);
	if (c->special > 0 && c->special <= 1)
		c = reflection(c, iray, normal);
	c = correct_light(c, iray, normal);
	return (clip(c));
}

t_color	*get_object_color(t_ray *ray)
{
	t_sphere	*s;
	t_plane		*p;
	t_color		*rslt;

	s = findSpheresIntersection(ray);
	p = findPlanesIntersection(ray);
	if ((s->radius < p->distance || p->distance == -1) && s->radius > ACCURACY)
		rslt = correct(s->color, ray, s->center, s->radius);
	else if ((p->distance <= s->radius || s->radius == -1) && p->distance > ACCURACY)
		rslt = correct(p->color, ray, p->normal, p->distance);
	else
		rslt = new_color(0, 0, 0, 0);
	return (rslt);
}

t_ray	*get_ray(t_camera *c, double x, double y)
{
	t_vect	*v1;
	t_vect	*v2;
	t_ray	*rslt;

	v1 = vectMult(c->camright, x - 0.5);
	v2 = vectMult(c->camdown, y - 0.5);
	v1 = vectAdd(v1, v2);
	v1 = vectAdd(c->camdir, v1);
	v1 = normalize(v1);

	rslt = new_ray(c->campos, v1);
	return (rslt);
}

double	get_x_point(int x)
{
	double	rslt;
	if (WD > HI)
		rslt = ((x + 0.5) / WD) * ASPR - (((WD - HI) / (double) HI) / 2);
	else
		rslt = (x + 0.5) / (double) WD;
	return (rslt);
}

double	get_y_point(int y)
{
	double	rslt;
	if (HI > WD)
		rslt = ((y + 0.5) / HI) / ASPR - (((HI - WD) / (double) WD) / 2);
	else
		rslt = (y + 0.5) / HI;
	return (rslt);
}

t_color	*get_color_at(int x, int y)
{
	t_color		*color;
	double		xamnt;
	double		yamnt;
	t_ray		*ray;
	t_camera	*c;

	xamnt = get_x_point(x);
	yamnt = get_y_point(y);
	c = get_scene()->cam;
	ray = get_ray(c, xamnt, yamnt);
	color = get_object_color(ray);
	return (color);
}

void	ft_draw_img(void)
{
	int	x;
	int	y;
	t_color	*c;

	x = 0;
	while (x < WD)
	{
		y = 0;
		while (y < HI)
		{
			c = get_color_at(x, y);
			mlx_put_pixel_to_image(x, y, get_color_number(c));
			y++;
		}
		x++;
	}
}

void	mlx_put_pixel_to_image(int x, int y, int color)
{
	unsigned int	new_color;
	int				i;
	t_win			*win;

	win = init_env();
	new_color = mlx_get_color_value(win->mlx, color);
	i = x * 4 + y * win->img->size_line;
	win->img->data[i] = (new_color & 0xFF);
	win->img->data[i + 1] = (new_color & 0xFF00) >> 8;
	win->img->data[i + 2] = (new_color & 0xFF0000) >> 16;
}
