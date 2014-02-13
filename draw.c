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
					ref_dir = normalize(vectAdd(negative(r->direction), vectMult(vectAdd(vectMult(n, dotProduct(n, r->direction)),r->direction), 2)));
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
	/*
	printf("%f, %f, %f : %f, %f, %f\n",
					r->origin->x,
					r->origin->y,
					r->origin->z,
					r->direction->x,
					r->direction->y,
					r->direction->z);
	// */
	return (rslt);
}

void	correct_light(t_color *c, t_ray *r, t_vect *n)
{
	c = c;
	r = r;
	n = n;
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_ray	*iray;


	iray = new_ray(vectAdd(ray->origin, vectMult(ray->direction,
										inter)), ray->direction);
	/*
	printf("%f, %f, %f : %f, %f, %f\n",
					iray->origin->x,
					iray->origin->y,
					iray->origin->z,
					iray->direction->x,
					iray->direction->y,
					iray->direction->z);
	*/
	if (c->special == 2)
		c = correct_plane(c, iray);
	if (c->special >= 0 && c->special <= 1)
		c = correct_sphere(c, iray, normal);
	correct_light(c, iray, normal);
	return (clip(c));
}

t_color	*get_object_color(t_ray *ray)
{
	t_sphere	*s;
	t_plane		*p;
	t_vect		*normal;
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
	{
		//printf("%f\n", s->radius);
		normal = s->center;
		rslt = s->color;
		rslt = correct(rslt, ray, normal, s->radius);
	}
	if ((p->distance <= s->radius || s->radius == -1) && p->distance > ACCURACY)
	{
		//printf("%f\n", p->distance);
		normal = p->normal;
		rslt = p->color;
		rslt = correct(rslt, ray, normal, p->distance);
	}
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
	yamnt = HI > WD ? ((y + 0.5) / HI) /	ASPECTRATIO -
		(((HI - WD) / (double) WD) / 2) : (y + 0.5) / HI;
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
