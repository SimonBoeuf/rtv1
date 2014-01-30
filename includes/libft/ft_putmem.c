/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 10:28:42 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/26 13:02:18 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmem(void *m)
{
	long unsigned int	zero;
	char				size;
	int					toprint;

	zero = 0xF0000000;
	ft_putstr("0x");
	size = sizeof(m);
	while (size-- > 0)
	{
		toprint = (int)(((long unsigned int)m & zero) >> size * 4);
		if (toprint == 0)
			ft_putchar('0');
		else
			ft_putnbr_base(toprint, 16);
		zero = zero >> 4;
	}
}
