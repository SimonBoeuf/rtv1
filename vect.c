#include "includes/rtv1.h"

t_vect	*new_vector(double x, double y, double z)
{
	t_vect	*v;

	v = (t_vect*)malloc(sizeof(t_vect));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

void	delete_vect(t_vect *v)
{
	free(v);
}

t_vect	*get_vector(int fd)
{
	double	x;
	double	y;
	double	z;
	char	*line;

	if(get_next_line(fd, &line) < 1)
			exit(-1);
	x = ft_atodouble(&line);
	y = ft_atodouble(&line);
	z = ft_atodouble(&line);
	return (new_vector(x, y, z));
}
