#include "includes/rtv1.h"

#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*test;
	double	rslt;

	test = "12345.678910, 456, 101112.13";
	rslt = ft_atodouble(&test);
	printf("%f\n", rslt);
	rslt = ft_atodouble(&test);
	printf("%f\n", rslt);
	rslt = ft_atodouble(&test);
	printf("%f\n", rslt);
	if (argc == 2)
		rtv1(argv[1]);
	return (0);
}
