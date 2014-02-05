#include "includes/rtv1.h"

void	display_scene(void)
{
	t_win	*window;

	window = init_env();
	window->img = init_img();

	ft_draw_img();
	mlx_put_image_to_window(window->mlx, window->win, window->img->img, 0, 0);
	mlx_loop(window->mlx);
}

void	rtv1(char *scene_file)
{
	init_scene(scene_file);
	display_scene();
}

void	init_scene(char *scene_file)
{
	int		fd;
	int		ret;
	char	*line;
	t_scene	*s;

	if ((fd = open(scene_file, O_RDONLY)) == -1)
		exit(-1);
	s = get_scene();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strcmp("camera:", line))
				s->cam = get_camera(fd);
		if (!ft_strcmp("spheres:", line))
				s->spheres = get_spheres(fd);
		if (!ft_strcmp("planes:", line))
				s->planes = get_planes(fd);
		if (!ft_strcmp("spots:", line))
				s->lights = get_spots(fd);
	}
	if (ret == -1)
			exit(-1);
}
