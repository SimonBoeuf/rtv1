/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:24:53 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/22 19:25:18 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*temp_s1;

	temp_s1 = s1;
	if (n == 0)
		return (s1);
	while (*s1 != '\0')
		s1++;
	while (n && *s2 != '\0')
	{
		*s1++ = *s2++;
		n--;
	}
	*s1 = '\0';
	return (temp_s1);
}
