#include "includes/rtv1.h"

void	ft_draw_img(void)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < WIN_WID)
	{
		y = 0;
		while (y < WIN_HEI)
		{
			color = get_colorAt(x, y);
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
