/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:59:34 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/15 11:04:19 by mstiedl          ###   ########.fr       */
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

double	which_quadrent(int x, int y, double i)
{
	if ((x > WIDTH / 2) && (y > HEIGHT / 2))
		return (i);
	if ((x <= WIDTH / 2) && (y > HEIGHT / 2))
		return (180 - i);
	if ((x <= WIDTH / 2) && (y <= HEIGHT / 2))
		return (180 + i);
	if ((x > WIDTH / 2) && (y <= HEIGHT / 2))
		return (360 - i);
	return (0);
}

double	find_start_angle(int x, int y, double hypot)
{
	double PI = 3.1415926535;
	double degree;
	int opposite;
	double sin;
	
	if (y <= (HEIGHT / 2))
		opposite = (HEIGHT / 2) - y;
	else
		opposite = y - (HEIGHT / 2);
	sin = (double)opposite / hypot;
	degree = asin(sin) * 180 / PI;
	degree = which_quadrent(x, y, degree);
	return (rnd(degree));
}

void	start_coord(t_map *map, double degree)
{
	map->x = map->x - (WIDTH / 2);
	map->y = make_grid_coord(map->y, 1);
	map->x = rnd((map->x * cos(degree)) - (map->y * sin(degree)));
	map->y = rnd((map->x * sin(degree)) + (map->y * cos(degree)));
	map->x = map->x + (WIDTH / 2);
	map->y = make_grid_coord(map->y, 0);
}

int make_grid_coord(int y, int arg)
{
	if (arg == 1)
	{
		if (y <= (HEIGHT / 2))
			y =  (HEIGHT / 2) - y;
		else
			y = -1 * (y - (HEIGHT / 2));	
	}
	else
	{
		if (y >= 0)
			y =  (HEIGHT / 2) - y;
		else
			y = (-1 * y) + (HEIGHT / 2);	
	}
	return (y);
}

void rotate_coord(t_map *map, double degree)
{
	double res_y;
	double res_x;
	
	map->x = map->x - (WIDTH / 2);
	map->y = make_grid_coord(map->y, 1);
	res_x = rnd((map->x * cos(THETA * degree)) - (map->y * sin(THETA * degree)));
	res_y = rnd((map->x * sin(THETA * degree)) + (map->y * cos(THETA * degree)));
	res_x = res_x + (WIDTH / 2);
	res_y = make_grid_coord(res_y, 0);
	map->x = res_x;
	map->y = res_y;
}

// void	calculate_down(t_map *map, t_dim dim, int degree, int first)
// {
// 	double x = 0;
// 	double y = 0;
// 	int i_down;

// 	i_down = 1;
// 	x = ((dim.ry * i_down) * sin(degree));
// 	while (map->down)
// 	{
// 		printf("x%i y%i\n", map->x, map->y);
// 		y = pythag(x, (dim.ry * i_down++));
// 		// printf("the difference: x%i y%i\n", x, y);
// 		map = map->down;
// 		map->x = map->x - rnd(x);
// 		map->y = first + rnd(y);
// 		x += x;
// 	}
// }
// void	calculate_next(t_map *map, t_dim dim, int degree)
// {
// 	double x = 0;
// 	double y = 0;
// 	static int i_next;

// 	printf("next :x%i y%i\n", map->x, map->y);
// 	y = map->y - ((dim.rx * ++i_next) * sin(degree));
// 	x = map->x + pythag(y, (dim.rx * i_next));
// 	map->next->y = rnd(y);
// 	map->next->x = rnd(x);
// 	// printf("the difference: x%i y%i\n", x, y);
// }
	// printf("-----NODE------\n|row(%i)col(%i)|\n---------------\n", map->row, map->col);
	// printf("original: x%i y%i\n", map->x, map->y);
	// printf("after: x%i y%i\n", map->x, map->y);