/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/30 17:38:11 by sboeuf            #+#    #+#             */
/*   Updated: 2014/01/30 18:07:52 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

#include <unistd.h>
#include <math.h>
#include "libft/libft.h"

typedef struct	s_color
{
	double	red;
	double	green;
	double	blue;
	double	special;
}				t_color;

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct s_camera
{
	t_vect	*campos;
	t_vect	*camdir;
	t_vect	*camright;
	t_vect	*camdown;
}

typedef struct	s_ray
{
	t_vect	*origin;
	t_vect	*direction;
}

typedef struct	s_light
{
	t_vect	*position;
	t_color	*color;
}

typedef struct	s_plane
{
	t_vect	*normal;
	double	distance;
	t_color	*color;
}				t_plane;

typedef struct	s_sphere
{
	t_vect	*center;
	double	radius;
	t_color	*color;
}				t_sphere;

/*
** Color
*/
double	brightness(t_color	*c);

#endif
