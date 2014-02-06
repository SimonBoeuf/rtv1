#include "./includes/rtv1.h"

t_win			*init_env(void)
{
	static t_win		*window = NULL;

	if (window == NULL)
	{
		if (!(window = (t_win*)malloc(sizeof(t_win))))
			exit(-1);
		window->mlx = mlx_init();
		window->win = mlx_new_window(window->mlx, WD, HI, "RTV1");
		window->img = init_img();
	}
	return (window);
}

void			env_del(void)
{
	t_win	*win;

	win = init_env();
	if (win)
	{
		free(win->mlx);
		free(win->win);
		img_del(win->img);
		free(win);
	}
}
