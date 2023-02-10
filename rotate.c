/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:59:34 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/10 18:20:43 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_radius(int x, int y)
{
	int x_len;
	int y_len;
	double radius;

	if (x <= (WIDTH / 2))
		x_len = (WIDTH / 2) - x;
	else
		x_len = x - (WIDTH / 2);
	if (y <= (HEIGHT / 2))
		y_len = (HEIGHT / 2) - y;
	else
		y_len = y - (HEIGHT / 2);
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

void	calculate_down(t_map *map, t_dim dim, int degree, int first)
{
	double x = 0;
	double y = 0;
	int i_down;

	i_down = 1;
	x = ((dim.ry * i_down) * sin(degree));
	while (map->down)
	{
		printf("x%i y%i\n", map->x, map->y);
		y = pythag(x, (dim.ry * i_down++));
		// printf("the difference: x%i y%i\n", x, y);
		map = map->down;
		map->x = map->x - rnd(x);
		map->y = first + rnd(y);
		x += x;
	}
}

void	calculate_next(t_map *map, t_dim dim, int degree)
{
	double x = 0;
	double y = 0;
	static int i_next;

	printf("next :x%i y%i\n", map->x, map->y);
	y = map->y - ((dim.rx * ++i_next) * sin(degree));
	x = map->x + pythag(y, (dim.rx * i_next));
	map->next->y = rnd(y);
	map->next->x = rnd(x);
	// printf("the difference: x%i y%i\n", x, y);
}

void	rotate_coord(t_map *map, int degree)
{
	double 	PI;
	double	i;
	int	r;
	// t_map *first;
	
	PI = 3.1415926535;
	r = get_radius(map->x, map->y);
	i = find_start_angle(map->x, map->y, r);
	printf("-----NODE------\n|row(%i)col(%i)|\n---------------\n", map->row, map->col);
	printf("original: x%i y%i\n", map->x, map->y);
	map->x = rnd((WIDTH / 2) + (r * cos((i + degree) * PI / 180)));
	map->y = rnd((HEIGHT / 2) + (r * sin((i + degree) * PI / 180)));
	printf("after: x%i y%i\n", map->x, map->y);
	// pixel_put(img, ((WIDTH / 2) + x), ((HEIGHT / 2) + y), 0x009900FF);
	// try use when making grid
	// first = map;
	// while (map)
	// {
	// 	calculate_down(map, dim, degree, first->y);
	// 	if (map->next == NULL)
	// 		break;
	// 	calculate_next(map, dim, degree);
	// 	map = map->next;
	// }
}

void ft_drawcircle2(t_img *img, int color)
{
    int x = 300;
	int y = 300;
    int d;
	int r = get_radius(x, y);
	// int i = 0;
	
	x = 0;
	y = r;
	d = 3 - 2 * r;
    while (x < 90)
	{
        pixel_put(img, x, y, color);
        // pixel_put(img, x, y, color);
        // pixel_put(img, WIDTH / 2 - x, HEIGHT / 2 + y, color);
        // pixel_put(img, WIDTH / 2 - x, HEIGHT / 2 - y, color);
        // pixel_put(img, WIDTH / 2 + y, HEIGHT / 2 + x, color);
        // pixel_put(img, WIDTH / 2 + y, HEIGHT / 2 - x, color);
        // pixel_put(img, WIDTH / 2 - y, HEIGHT / 2 + x, color);
        // pixel_put(img, WIDTH / 2 - y, HEIGHT / 2 - x, color);
        if (d < 0)
            d = d + 4 * x + 6;
        else
		{
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}