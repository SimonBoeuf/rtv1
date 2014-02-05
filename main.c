#include "includes/rtv1.h"

int	main(int argc, char **argv)
{
	t_scene		*test;
	t_sphere	*test2;
	t_light		*test3;
	t_plane		*test4;
	t_camera	*test5;

	test = new_scene();
	if (test == NULL)
		write(1, "nok\n", 3);
	if (test->lights != NULL)
		write(1, "nok\n", 3);
	if (test->spheres != NULL)
		write(1, "nok\n", 3);
	if (test->planes != NULL)
		write(1, "nok\n", 3);
	if (test->cam != NULL)
		write(1, "nok\n", 3);
	test2 = new_sphere(NULL, 0.0, NULL);
	test3 = new_light(NULL, NULL);
	test4 = new_plane(NULL, 0.0, NULL);
	test5 = new_camera(NULL, NULL, NULL, NULL);
	test->lights = test3;
	test->spheres = test2;
	test->planes = test4;
	test->cam = test5;
	if (test->lights == NULL)
		write(1, "nok\n", 3);
	if (test->spheres == NULL)
		write(1, "nok\n", 3);
	if (test->planes == NULL)
		write(1, "nok\n", 3);
	if (test->cam == NULL)
		write(1, "nok\n", 3);
	delete_scene(test);
	if (test->lights != NULL)
		ft_putendl("light should be null");
	if (test->spheres != NULL)
		ft_putendl("spheres should be null");
	if (test->planes != NULL)
		ft_putendl("planes should be null");
	if (argc == 2)
		rtv1(argv[1]);
	return (0);
}
