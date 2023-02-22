/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:17:01 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 16:53:35 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	my_ternery(int a, int b, int yes, int no)
{
	if (a > b)
		return (yes);
	else
		return (no);
}

void	error(char *str, t_fdf *fdf, int arg)
{
	free_list(fdf->map);
	if (arg == 1)
		ft_putendl_fd(str, 2);
	free (fdf);
	exit(arg);
}

void	free_data(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free (data[i]);
		i++;
	}
	free (data);
}

int	get_z_max(t_map *map)
{
	t_map	*temp;
	int		max;

	temp = map->next;
	max = map->z;
	while (temp)
	{
		if (max < temp->z)
			max = temp->z;
		temp = temp->next;
	}
	return (max);
}

int	get_z_min(t_map *map)
{
	t_map	*temp;
	int		min;

	temp = map->next;
	min = map->z;
	while (temp)
	{
		if (min > temp->z)
			min = temp->z;
		temp = temp->next;
	}
	return (min);
}
