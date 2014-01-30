/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:16:51 by mchoong           #+#    #+#             */
/*   Updated: 2013/12/02 16:06:36 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		size_dst;
	size_t		size_src;
	size_t		temp_size;

	temp_size = size;
	size_dst = 0;
	size_src = ft_strlen(src);
	while (size != 0 && *dst != '\0')
	{
		size--;
		size_dst++;
		dst++;
	}
	if (size == 0)
		return (temp_size + size_src);
	while (size > 1 && *src != '\0')
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (size_dst + size_src);
}
