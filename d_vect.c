/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_vect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:17:49 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:17:51 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

double	dotProduct(t_vect *v1, t_vect *v2)
{
	double dotProduct;

	dotProduct = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (dotProduct);
}

double	magnitude(t_vect *v)
{
	return (sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
}
