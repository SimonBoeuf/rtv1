/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_tail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 13:55:56 by mchoong           #+#    #+#             */
/*   Updated: 2013/12/03 13:58:03 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_tail(t_list **alst, t_list *new)
{
	t_list		*temp;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			temp = *alst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
		}
	}
}
