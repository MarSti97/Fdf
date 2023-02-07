/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:59:34 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/07 17:31:21 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	rotate(t_map *map)
// {
	
// }

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
	int degree;
	int opposite;
	
	if (y <= (HEIGHT / 2))
		opposite = (HEIGHT / 2) - y;
	else
		opposite = y - (HEIGHT / 2);
	degree = asin(opposite / hypot);
	degree = which_quadrent(x, y, degree);
	return (degree);
}

void	draw_circle(t_img *img)
{
	double PI = 3.1415926535;
	int x = 345;
	int y = 245;
	int	i;
	int r;
	
	r = get_radius(x, y);
	i = find_start_angle(x, y, r);
		x = r * cos(i * PI / 180);
		y = r * sin(i * PI / 180);
		pixel_put(img, ((WIDTH / 2) + x), ((HEIGHT / 2) + y), 0x009900FF);
	// try use when making grid
}