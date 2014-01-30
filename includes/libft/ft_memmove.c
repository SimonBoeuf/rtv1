/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 09:35:12 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/22 17:27:13 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	void	*temp_s1;

	temp_s1 = s1;
	if (!n)
		return (s1);
	if (s1 <= s2 || (unsigned char *)s1 > ((unsigned char *)s2 + n))
		return (ft_memcpy(s1, s2, n));
	else
	{
		s1 = (unsigned char *)s1 + n - 1;
		s2 = (unsigned char *)s2 + n - 1;
		while (n--)
			*(unsigned char *)s1-- = *(unsigned char *)s2--;
	}
	return (temp_s1);
}
