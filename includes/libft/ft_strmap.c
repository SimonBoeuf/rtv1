/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 19:30:59 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/25 11:33:04 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*result;
	char	*temp_result;

	if (s == NULL)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (result == NULL)
		return (NULL);
	temp_result = result;
	while (*s != '\0')
	{
		*temp_result = (*f)(*s);
		temp_result++;
		s++;
	}
	*temp_result = '\0';
	return (result);
}
