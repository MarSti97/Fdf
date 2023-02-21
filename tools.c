/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:17:01 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 22:27:08 by mstiedl          ###   ########.fr       */
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
	if (fdf->mlx && fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx && fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (arg == 1)
		ft_putendl_fd(str, 2);
	free (fdf);
	exit(arg);
}

void	pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;
	
	if (x > WIDTH || x < 0 || y < 0 || y > HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = colour;
}

int get_z_max(t_map *map)
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

int get_z_min(t_map *map)
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
