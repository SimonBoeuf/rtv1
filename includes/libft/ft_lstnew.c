/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 09:47:08 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/30 18:38:28 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (ret == NULL)
		return (NULL);
	ret->next = NULL;
	if (content == NULL)
	{
		ret->content = NULL;
		(*ret).content_size = 0;
		return (ret);
	}
	if ((ret->content = (void *)malloc(content_size)) == NULL)
		return (NULL);
	ft_memcpy(ret->content, content, content_size);
	ret->content_size = content_size;
	return (ret);
}
