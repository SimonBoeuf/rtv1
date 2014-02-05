#include "includes/rtv1.h"

int		winningObjIndex(double *objs)
{
	int		min_val_index;
	double	min;
	int		i;

	if (objs != NULL)
	{
		min = 0;
		i = 0;
		min_val_index = -1;
		while (objs[i] != 0)
		{
			if ((min > objs[i] || min == 0) && objs[i++] > 0)
			{
					min = objs[i - 1];
					min_val_index = i - 1;
			}
		}
		return (min_val_index);
	}
	return (-1);
}

void	rtv1(char *scene_file)
{
	int		fd;

	if ((fd = open(scene_file, O_RDONLY)) == -1)
		exit(-1);
	scene_file = scene_file;
}
