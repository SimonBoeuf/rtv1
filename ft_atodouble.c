/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboeuf <sboeuf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:58:02 by sboeuf            #+#    #+#             */
/*   Updated: 2014/02/16 19:29:30 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

double	ft_atodouble(char **str)
{
	double	value;
	int		sign;
	int		i;

	value = 0;
	sign = (**str == '-') ? -1 : 1;
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		i = 1;
		while (ft_isdigit(**str))
		{
			value += (double)(**str - '0') / pow(10, i++);
			(*str)++;
		}
	}
	*str += 2;
	return (value * sign);
}
