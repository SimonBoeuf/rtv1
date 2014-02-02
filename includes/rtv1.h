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
#include "libft/includes/libft.h"

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
}				t_camera;

typedef struct	s_ray
{
	t_vect	*origin;
	t_vect	*direction;
}				t_ray;

typedef struct	s_light
{
	t_vect	*position;
	t_color	*color;
}				t_light;

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

void		rtv1(char *file);

/*
** Color
*/
t_color		*new_color(double red, double green, double blue, double special);
void		delete_color(t_color *c);

double		brightness(t_color *c);
t_color		*colorScalar(double scalar, t_color *c1);
t_color		*colorAdd(t_color *c1, t_color *c2);
t_color		*colorMultiply(t_color *c1, t_color *c2);

/*
** Vector
*/
t_vect		*new_vector(double x, double y, double z);
void		delete_vect(t_vect *v);

t_vect		*normalize(t_vect *v1);
t_vect		*negative(t_vect *v1);
t_vect		*crossProduct(t_vect *v1, t_vect *v2);
t_vect		*vectAdd(t_vect *v1, t_vect *v2);
t_vect		*vectMult(t_vect *v1, double scalar);

double		dotProduct(t_vect *v1, t_vect *v2);
double		magnitude(t_vect *v);

/*
** Camera
*/
t_camera	*new_camera(t_vect *p, t_vect *di, t_vect *r, t_vect *dwn);
void		delete_camera(t_camera *c);

/*
** Ray
*/
t_ray		*new_ray(t_vect *o, t_vect *d);
void		delete_ray(t_ray *r);

/*
** Light
*/
t_light		*new_light(t_vect *p, t_color *c);
void		delete_light(t_light *l);

/*
** Plane
*/
t_plane		*new_plane(t_vect *normal, double distance, t_color *c);
double		findPlaneIntersection(t_plane *p, t_ray *ray);
void		delete_plane(t_plane *p);

/*
** Sphere
*/
t_sphere	*new_sphere(t_vect *center, double radius, t_color *color);
t_vect		*getNormalAtSphere(t_sphere *sphere, t_vect *point);
void		delete_sphere(t_sphere *s);
#endif
