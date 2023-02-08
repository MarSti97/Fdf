/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:59:34 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/08 20:56:19 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_radius(int x, int y)
{
	int x_len;
	int y_len;
	int radius;

	if (x <= (WIDTH / 2))
		x_len = (WIDTH / 2) - x;
	else
		x_len = x - (WIDTH / 2);
	if (y <= (HEIGHT / 2))
		y_len = (HEIGHT / 2) - y;
	else
		y_len = y - (HEIGHT / 2);
	radius = (x_len * x_len) + (y_len * y_len);
	return (sqrt(radius));
}

int	which_quadrent(int x, int y, int i)
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

int	find_start_angle(int x, int y, int hypot)
{
	double PI = 3.1415926535;
	int degree;
	int opposite;
	double sin;
	
	if (y <= (HEIGHT / 2))
		opposite = (HEIGHT / 2) - y;
	else
		opposite = y - (HEIGHT / 2);
	// ft_printf("opposite: %i\n", opposite);
	sin = (double)opposite / (double)hypot;
	// printf("sin: %f\n", sin);
	degree = asin(sin) * 180/PI;
	// printf("degree: %f\n", degree);
	degree = which_quadrent(x, y, degree);
	return (degree);
}

void	rotate_coord(t_map *map, int degree)
{
	double PI = 3.1415926535;
	int	i;
	int r;
	
	r = get_radius(map->x, map->y);
	i = find_start_angle(map->x, map->y, r);
	map->x = (WIDTH / 2) + (r * cos((i + degree) * PI / 180));
	map->y = (HEIGHT / 2) + (r * sin((i + degree) * PI / 180));
	// pixel_put(img, ((WIDTH / 2) + x), ((HEIGHT / 2) + y), 0x009900FF);
	// try use when making grid
}

// void	test_rotating(t_img *img)
// {
// 	double PI = 3.1415926535;
// 	int x = 300;
// 	int	y = 240;
// 	int r;
// 	int i;
// 	int j = 0;
	
// 	r = get_radius(x, y);
// 	// ft_printf("radius: %i\n", r);
// 	i = find_start_angle(x, y, r);
// 	// ft_printf("angle: %i\n", i);
// 	while (j++ < 5)
// 	{
// 		i++;
// 		x = (r * cos(i * PI / 180));
// 		y = (r * sin(i * PI / 180));
// 		pixel_put(img, ((WIDTH / 2) + x), ((HEIGHT / 2) + y), 0x009900FF);	
// 	}
// }