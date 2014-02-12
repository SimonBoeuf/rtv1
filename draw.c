#include "includes/rtv1.h"
#include <stdio.h>

void	correct_plane(t_color *c, t_ray *ray)
{
	int	square;

	square = (int)floor(ray->origin->x) + (int)floor(ray->origin->z);
	if (square % 2 == 0)
	{
		c->red = 0;
		c->green = 0;
		c->blue = 0;
	}
	else
	{
		c->red = 1;
		c->green = 1;
		c->blue = 1;
	}
}

void	correct_sphere(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_vect	*reflection;
	t_ray	*ref_ray;

	reflection = vectAdd(negative(ray->direction),
		vectMult(vectAdd(vectMult(normal, dotProduct(normal,
						negative(ray->direction))), ray->direction), 2));
	ref_ray = new_ray(ray->origin, reflection);
	ref_ray = ref_ray;	
	c = c;
	ray = ray;
	normal = normal;
	inter = inter;
}

t_color	*correct(t_color *c, t_ray *ray, t_vect *normal, double inter)
{
	t_ray	*tmp;


	tmp = new_ray(vectAdd(ray->origin, vectMult(ray->direction,
										inter)), ray->direction);
	if (c->special == 2)
		correct_plane(c, tmp);
	if (c->special >= 0 && c->special <= 1)
		correct_sphere(c, tmp, normal, inter);
	return (clip(colorScalar(AMBIENTLIGHT, c)));
}

t_color	*get_object_color(t_ray *ray)
{
	t_sphere	*s;
	t_plane		*p;
	t_vect		*normal;
	t_color		*rslt;

	rslt = new_color(0, 0, 0, 0);
	s = findSpheresIntersection(ray);
	p = findPlanesIntersection(ray);
	if ((s->radius < p->distance || p->distance == -1) && s->radius > ACCURACY)
	{
		normal = s->center;
		rslt = s->color;
		rslt = correct(rslt, ray, normal, s->radius);
		printf("sphere wins : %f\n", s->radius);
	}
	else if ((p->distance <= s->radius || s->radius == -1) && p->distance > ACCURACY)
	{
		normal = p->normal;
		rslt = p->color;
		rslt = correct(rslt, ray, normal, p->distance);
		printf("plane wins : %f\n", p->distance);
	}
			//printf("%f : %f : %f\n %f : %f : %f\n", ray->origin->x, ray->origin->y, ray->origin->z, ray->direction->x, ray->direction->y, ray->direction->z);
			//printf("%f : %f : %f\n %f : %f : %f\n", tmp->origin->x, tmp->origin->y, tmp->origin->z, tmp->direction->x, tmp->direction->y, tmp->direction->z);
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
	yamnt = HI > WD ? (((HI - y) + 0.5) / HI) /	ASPECTRATIO -
		(((HI - WD) / (double) WD) / 2) : ((HI - y) + 0.5) / HI;
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
