/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:11:24 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/22 16:29:18 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*temp_b;

	temp_b = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (temp_b);
}
