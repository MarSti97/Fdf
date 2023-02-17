/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:59:34 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/17 13:08:39 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_radius(t_map *start, t_map *end)
{
	int x_len;
	int y_len;
	double radius;
	
	x_len = (start->x > end->x ? start->x - end->x : end->x - start->x);
	y_len = (start->y > end->y ? start->y - end->y : end->y - start->y);
	radius = pythag(x_len, y_len);
	return (radius);
}

int make_grid_coord(int y, int arg, int height)
{
	if (arg == 1)
	{
		if (y <= (height))
			y =  (height) - y;
		else
			y = -1 * (y - (height));	
	}
	else
	{
		if (y >= 0)
			y =  (height) - y;
		else
			y = (-1 * y) + (height);	
	}
	return (y);
}

void rotate_coord(t_map *map, double degree, t_dim dim)
{
	double res_y;
	double res_x;
	
	map->x = map->x - (dim.cntrx);
	map->y = make_grid_coord(map->y, 1, dim.cntry);
	res_x = rnd((map->x * cos(THETA * degree)) - (map->y * sin(THETA * degree)));
	res_y = rnd((map->x * sin(THETA * degree)) + (map->y * cos(THETA * degree)));
	res_x = res_x + (dim.cntrx);
	res_y = make_grid_coord(res_y, 0, dim.cntry);
	map->x = res_x;
	map->y = res_y;
}

void tilt(t_map *map, double degree, t_dim dim)
{
	double res_y;
	
	map->y = make_grid_coord(map->y, 1, dim.cntry);
	res_y = rnd((map->y * cos(THETA * degree)));
	res_y = make_grid_coord(res_y, 0, dim.cntry);
	map->y = res_y;
}

void spin(t_map *map, double degree, t_dim dim)
{
	double res_x;
	double res_y;
	
	map->x = map->x - (dim.cntrx);
	map->y = make_grid_coord(map->y, 1, dim.cntry);
	res_x = rnd((map->x * cos(THETA * degree)) + (map->y * sin(THETA * degree)));
	res_y = rnd((map->x * sin(THETA * degree)) + (map->y * cos(THETA * degree)));
	// res_x = rnd((map->x * cos(THETA * degree)));
	res_x = res_x + (dim.cntrx);
	map->x = res_x;
	res_y = make_grid_coord(res_y, 0, dim.cntry);
	map->y = res_y;
}