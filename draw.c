#include "includes/rtv1.h"
#include <stdio.h>

t_color	*correct_plane(t_color *c, t_ray *iray)
{
	int		square;
	t_color	*rslt;

	c = c;
	square = (int)floor(iray->origin->x) + (int)floor(iray->origin->z);
	if (square % 2 == 0)
	{
		rslt = new_color(0, 0, 0, c->special);
	}
	else
	{
		rslt = new_color(c->red, c->green, c->blue, 2);
	}
	return (rslt);
}

t_color	*correct_sphere(t_color *c, t_ray *r, t_vect *n)
{
	c = c;
	r = r;
	n = n;
	return (c);
}
t_ray	*get_ref_ray(t_vect *n, t_ray *r)
{
	t_ray	*ref_ray;
	t_vect	*scalar1;
	t_vect	*scalar2;
	t_vect	*add1;
	t_vect	*add2;

	scalar1 = vectMult(n, dotProduct(n, negative(r->direction)));
	add1 = vectAdd(scalar1, r->direction);
	scalar2 = vectMult(add1, 2);
	add2 = vectAdd(negative(r->direction), scalar2);
	ref_ray = new_ray(r->origin, normalize(add2));
	free(scalar1);
	free(add1);
	free(scalar2);
	free(add2);
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
						specular = pow(specular, 10);
						rslt = colorAdd(rslt, colorScalar(specular * c->special, l->color));
					}
				}
			}
		}
		l = l->next;
	}
	return (rslt);
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter);
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
		ref_inter_ray = new_ray(vectAdd(r->origin, vectMult(ref->direction, s->radius)), ref->direction);
		rslt = reflection(c, ref_inter_ray, s->center);
	}
	else if ((p->distance <= s->radius || s->radius == -1) && p->distance > ACCURACY)
	{
		ref_inter_ray = new_ray(vectAdd(r->origin, vectMult(ref->direction, p->distance)), ref->direction);
		rslt = correct_plane(c, ref_inter_ray);
	}
	else
		rslt = c;
	return (rslt);
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_ray	*iray;

	iray = new_ray(vectAdd(ray->origin, vectMult(ray->direction,
										inter)), ray->direction);
	if (c->special == 2)
		c = correct_plane(c, iray);
	if (c->special >= 0 && c->special <= 1)
		c = reflection(c, iray, normal);
	c = correct_light(c, iray, normal);
	return (clip(c));
}

t_color	*get_object_color(t_ray *ray)
{
	t_sphere	*s;
	t_plane		*p;
	t_color		*rslt;
	/*
	printf("%f, %f, %f : %f, %f, %f\n",
					ray->origin->x,
					ray->origin->y,
					ray->origin->z,
					ray->direction->x,
					ray->direction->y,
					ray->direction->z);
					*/
	rslt = new_color(0, 0, 0, 0);
	s = findSpheresIntersection(ray);
	p = findPlanesIntersection(ray);
	if ((s->radius < p->distance || p->distance == -1) && s->radius > ACCURACY)
		rslt = correct(s->color, ray, s->center, s->radius);
	if ((p->distance <= s->radius || s->radius == -1) && p->distance > ACCURACY)
		rslt = correct(p->color, ray, p->normal, p->distance);
	return (rslt);
}

t_color	*get_color_at(int x, int y)
{
	t_color		*color;
	double		xamnt;
	double		yamnt;
	t_ray		*ray;
	t_camera	*c;

	xamnt = WD > HI ? ((x + 0.5) / WD) * ASPECTRATIO - (((WD - HI)
		/ (double) HI) / 2) : (x + 0.5) / WD;
	yamnt = HI > WD ? ((HI - y + 0.5) / HI) / ASPECTRATIO -
		(((HI - WD) / (double) WD) / 2) : (HI - y + 0.5) / HI;
	c = get_scene()->cam;
	ray = new_ray(c->campos, normalize(vectAdd(c->camdir, vectAdd(vectMult(
											c->camright, xamnt - 0.5),
										vectMult(c->camdown, yamnt - 0.5)))));
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
			mlx_put_pixel_to_image(x, HI - y, get_color_number(c));
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
