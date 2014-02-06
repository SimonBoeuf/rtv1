#include "./includes/rtv1.h"

void			ft_exit(void)
{
	t_scene	*s;

	s = get_scene();
	env_del();
	delete_scene(s);
	exit(0);
}

int		ft_key_hook(int keycode)
{
	if (keycode == KEYECHAP)
		ft_exit();
	return (0);
}

int			ft_expose_hook(void)
{
	t_win	*window;

	window = init_env();
	mlx_put_image_to_window(window->mlx, window->win, window->img->img, 0, 0);
	return (0);
}
