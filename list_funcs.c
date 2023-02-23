/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:12:46 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 12:59:00 by mstiedl          ###   ########.fr       */
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
}

void	free_list(t_map *lst)
{
	t_map	*temp;
	t_map	*down;

	while (lst)
	{
		if (lst->down)
			down = lst->down;
		else
			down = NULL;
		while (lst)
		{
			temp = lst;
			lst = lst->next;
			free (temp);
		}
		if (down)
			lst = down;
	}
	exit (0);
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
