/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:18:58 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:18:59 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rtv1.h"

t_img			*init_img(void)
{
	t_win	*win;
	t_img	*img;

	win = init_env();
	img = (t_img*)malloc(sizeof(t_img));
	img->img = mlx_new_image(win->mlx, WD, HI);
	img->data = mlx_get_data_addr(img->img, &img->bbp,
									&img->size_line, &img->endian);
	return (img);
}

void			img_del(t_img *img)
{
	if (img)
	{
		if (img->img != NULL)
			free(img->img);
		free(img);
	}
}
