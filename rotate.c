/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:59:34 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 17:18:31 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	make_grid_coord(int y, int arg, int height)
{
	if (arg == 1)
	{
		if (y <= (height))
			y = (height) - y;
		else
			y = -1 * (y - (height));
	}
	else
	{
		if (y >= 0)
			y = (height) - y;
		else
			y = (-1 * y) + (height);
	}
	return (y);
}

void	rotate_coord(t_map *map, double deg, t_dim dim)
{
	double	res_y;
	double	res_x;
	double	pi;

	pi = M_PI / 180;
	map->x = map->x - (dim.cntrx);
	map->y = make_grid_coord(map->y, 1, dim.cntry);
	res_x = rnd((map->x * cos(pi * deg)) - (map->y * sin(pi * deg)));
	res_y = rnd((map->x * sin(pi * deg)) + (map->y * cos(pi * deg)));
	res_x = res_x + (dim.cntrx);
	res_y = make_grid_coord(res_y, 0, dim.cntry);
	map->x = res_x;
	map->y = res_y;
}

void	tilt(t_map *map, double degree, t_dim dim)
{
	double	res_y;
	double	pi;

	pi = M_PI / 180;
	map->y = make_grid_coord(map->y, 1, dim.cntry);
	res_y = rnd((map->y * cos(pi * degree)));
	res_y = make_grid_coord(res_y, 0, dim.cntry);
	map->y = res_y;
	tilt_3d(map, dim);
}

void	spin(t_map *map, double degree, t_dim dim)
{
	double	res_x;
	double	pi;

	pi = M_PI / 180;
	map->x = map->x - (dim.cntrx);
	res_x = rnd((map->x * cos(pi * degree)));
	res_x = res_x + (dim.cntrx);
	map->x = res_x;
	spin_3d(map, dim);
}
