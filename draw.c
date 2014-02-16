#include "includes/rtv1.h"

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
