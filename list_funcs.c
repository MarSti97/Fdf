/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:12:46 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/12 20:42:05 by mstiedl          ###   ########.fr       */
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

void	error(t_map *lst)
{
	t_map	*temp;

	if (lst)
	{
		// write(1, "Memory error\n", 13);
		while (lst != NULL)
		{
			temp = lst;
			lst = lst->next;
			free (temp);
		}
	}
	exit(1);
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