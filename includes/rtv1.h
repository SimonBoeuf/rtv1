/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/30 17:38:11 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 18:40:10 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include "libft/includes/libft.h"

# define BUFF_SIZE 32

# define KEYECHAP 65307

# define WD 640
# define HI 480

# define AADEPTH 1
# define AATHRESHOLD 0.1
# define ASPR ((double)WD / (double)HI)
# define AMBIENTLIGHT 0.2
# define ACCURACY 0.00000001

typedef struct			s_img
{
	void				*img;
	char				*data;
	int					bbp;
	int					size_line;
	int					endian;
}						t_img;

typedef struct			s_win
{
	void				*mlx;
	void				*win;
	t_img				*img;
}						t_win;

typedef struct			s_color
{
	double				red;
	double				green;
	double				blue;
	double				special;
}						t_color;

typedef struct			s_vect
{
	double				x;
	double				y;
	double				z;
}						t_vect;

typedef struct			s_ray
{
	t_vect				*origin;
	t_vect				*direction;
}						t_ray;

typedef struct			 s_camera
{
	t_vect				*campos;
	t_vect				*camdir;
	t_vect				*camright;
	t_vect				*camdown;
}						t_camera;

typedef struct			s_inter
{
	t_vect				*normal;
	double				dist;
	t_color				*c;
}						t_inter;

typedef struct			s_light
{
	t_vect				*position;
	t_color				*color;
	struct s_light		*next;
}						t_light;

typedef struct			s_plane
{
	t_vect				*normal;
	double				distance;
	t_color				*color;
	struct s_plane		*next; 
}						t_plane;

typedef struct			s_sphere
{
	t_vect				*center;
	double				radius;
	t_color				*color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_cylinder
{
	t_vect				*center;
	double				radius;
	t_color				*color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct			s_scene
{
	t_camera			*cam;
	t_light				*lights;
	t_plane				*planes;
	t_sphere			*spheres;
	t_cylinder			*cylinders;
}						t_scene;

/*
** Debug print TODO remove
*/
void	print_scene(t_scene *s);
void	print_camera(t_camera *c);
void	print_light(t_light *l);
void	print_ray(t_ray *r);
void	print_plane(t_plane *p);
void	print_sphere(t_sphere *s);
void	print_vect(t_vect *v);
void	print_color(t_color *c);

/*
** Core
*/
void		rtv1(char *file);
void		init_scene(char *file);
void		display_scene(void);

/*
** Img
*/
t_img		*init_img(void);
void		img_del(t_img *img);

/*
** Hooks
*/
void		ft_exit(void);
int			ft_key_hook(int keycode);
int			ft_expose_hook(void);

/*
** Window
*/
t_win		*init_env(void);
void		env_del(void);

/*
** Draw
*/
void		mlx_put_pixel_to_image(int x, int y, int color);
void		ft_draw_img(void);

/*
** GetNextLine & misc
*/
int			get_next_line(int const fd, char **line);
double		ft_atodouble(char **s);

/*
** Color
*/
t_color		*new_color(double red, double green, double blue, double special);
void		delete_color(t_color *c);
t_color		*cpy_color(t_color *c);
t_color		*get_color(int fd);
int			get_color_number(t_color *c);

t_color		*colorScalar(double scalar, t_color *c1);
t_color		*colorAdd(t_color *c1, t_color *c2);
t_color		*colorMultiply(t_color *c1, t_color *c2);
t_color		*colorAverage(t_color *c1, t_color *c2);
t_color		*clip(t_color *c1);

t_color		*reflection(t_color *c, t_ray *r, t_vect *normal);
t_color		*square_plane(t_color *c, t_ray *iray, t_vect *n);
t_color		*correct_light(t_color *c, t_ray *r, t_vect *n);
t_color		*correct(t_color *c, t_ray *ray, t_vect *normal, double inter);
t_color		*get_object_color(t_ray *ray);

/*
** Vector
*/
t_vect		*new_vector(double x, double y, double z);
void		delete_vect(t_vect *v);
t_vect		*get_vector(int fd);
t_vect		*cpy_vect(t_vect *v);

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
t_camera	*get_camera(int fd);

/*
** Ray
*/
t_ray		*new_ray(t_vect *o, t_vect *d);
t_ray		*cpy_ray(t_ray *r);
void		delete_ray(t_ray *r);

t_ray		*get_intersection_ray(t_ray *r, double inter);
t_ray		*get_ref_ray(t_vect *n, t_ray *r);
t_ray		*get_ray(t_camera *c, double x, double y);

/*
** Light
*/
t_light		*new_light(t_vect *p, t_color *c);
void		add_light(t_light *start, t_light *new);
void		delete_lights(t_light **l);

t_light		*get_spots(int fd);
t_light		*get_spot(int fd);

/*
** Intersection
*/

t_inter		*new_inter(t_vect *n, double dist, t_color *c);
t_inter		*min_inter(t_inter *i, t_inter *i2);
t_inter		*find_min_inter(t_ray *r);

/*
** Plane
*/
t_plane		*new_plane(t_vect *normal, double distance, t_color *c);
void		add_plane(t_plane *start, t_plane *new);
t_inter		*findPlanesIntersection(t_ray *ray);
double		findPlaneIntersection(t_plane *p, t_ray *ray);
void		delete_planes(t_plane **p);

t_plane		*get_planes(int fd);
t_plane		*get_plane(int fd);

/*
** Sphere
*/
t_sphere	*new_sphere(t_vect *center, double radius, t_color *color);
void		add_sphere(t_sphere *start, t_sphere *new);
void		delete_spheres(t_sphere **s);

t_inter		*findSpheresIntersection(t_ray *r);
double		findSphereIntersection(t_sphere *s, t_ray *r);
t_vect		*getNormalAtSphere(t_sphere *sphere, t_vect *point);
t_sphere	*get_spheres(int fd);
t_sphere	*get_sphere(int fd);

/*
** Cylinder
*/
t_cylinder	*new_cylinder(t_vect *center, double radius, t_color *color);
void		add_cylinder(t_cylinder *start, t_cylinder *new);
void		delete_cylinders(t_cylinder **s);

t_inter		*findCylindersIntersection(t_ray *r);
double		findCylinderIntersection(t_cylinder *c, t_ray *r);
t_vect		*getNormalAtCylinder(t_cylinder *c, t_vect *point);
t_cylinder	*get_cylinders(int fd);
t_cylinder	*get_cylinder(int fd);

/*
** Scene
*/
t_scene		*new_scene(void);
t_scene		*get_scene(void);
void		delete_scene(t_scene *s);

#endif
