/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:24:41 by mchoong           #+#    #+#             */
/*   Updated: 2013/12/02 16:06:58 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*result;
	char const	*end;
	char const	*start;

	start = NULL;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (!(*s == ' ' || *s == '\n' || *s == '\t'))
		{
			start = (start == NULL) ? s : start;
			end = s;
		}
		s++;
	}
	if (start == NULL)
		return (ft_strnew(0));
	if ((result = (char *)malloc(sizeof(char) * (end - start + 2))) == NULL)
		return (NULL);
	s = start;
	while (s <= end)
		*result++ = *s++;
	*result = '\0';
	return (result - (end - start + 1));
}
