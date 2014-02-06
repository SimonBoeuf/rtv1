#include "includes/rtv1.h"
t_color	*get_object_color(t_ray *ray)
{
	double		mininter;
	double		inter;
	t_color		*rslt;
	t_sphere	*s;
	t_plane		*p;

	mininter = -1;
	ray = ray;

	rslt = new_color(0, 0, 0, 0);
	s = get_scene()->spheres;
	while (s != NULL)
	{
		inter = findSphereIntersection(s, ray);
		if (inter > 0 && (inter < mininter || mininter == -1))
		{
			mininter = inter;
			if (mininter > ACCURACY)
				rslt = s->color;
		}
		s = s->next;
	}
	p = get_scene()->planes;
	while (p != NULL)
	{
		inter = findPlaneIntersection(p, ray);
		if (inter > 0 && (inter < mininter  - 1 || mininter == -1))
		{
			mininter = inter;
			if (mininter > ACCURACY)
				rslt = p->color;
		}
		p = p->next;
	}
	return (rslt);
}

t_color	*get_color_at(int x, int y)
{
	t_color		*color;
	int			xamnt;
	int			yamnt;
	t_ray		*ray;
	t_camera	*c;

	xamnt = WD > HI ? ((x + 0.5) / WD) * ASPECTRATIO - (((WD - HI)
		/ (double) HI) / 2) : (x + 0.5) / WD;
	yamnt = HI > WD ? (((HI - y) + 0.5) / HI) /	ASPECTRATIO -
		(((HI - WD) / (double) WD) / 2) :
		((HI - y) + 0.5) / HI;
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
	int	color;

	x = 0;
	while (x < WD)
	{
		y = 0;
		while (y < HI)
		{
			color = get_color_number(get_color_at(x, y));
			mlx_put_pixel_to_image(x, y, color);
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
