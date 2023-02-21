/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:12:46 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 21:09:18 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_listadd_back(t_map **lst, t_map *new)
{
	t_map	*temp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_listlast(*lst);
	temp->next = new;
	// new->prev = temp;
}

void	free_list(t_map *lst)
{
	t_map	*temp;
	t_map	*down;

	down = lst;
	while (lst)
	{
		lst = down;
		if (lst->down)
			down = lst->down;
		while (lst)
		{
			temp = lst;
			lst = lst->next;
			free (temp);	
		}
	}
}

t_map	*ft_listlast(t_map *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}