/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:20 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/16 21:37:54 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int keys(int keycode, t_fdf *fdf);

int close_x()
{
	exit (0);
	return (0);
}

void controls(t_fdf *fdf, t_img *img)
{
	fdf->img = img;
	// mlx_key_hook(fdf->win, keys, fdf);
	mlx_hook(fdf->win, 2, 1L<<0, keys, fdf);
	mlx_hook(fdf->win, 17, 1L<<2, close_x, fdf);
	mlx_mouse_hook(fdf->win, zoom, fdf);
}

int keys(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
		exit (0);
	if (keycode == E) // rotate right
		fdf->dim.rotate -= 1;
	else if (keycode == Q) // rotate left
		fdf->dim.rotate += 1;
	else if (keycode == W) 	// tilt up
		fdf->dim.tilt += 1;
	else if (keycode == S) // tilt down
		fdf->dim.tilt -= 1;
	else if (keycode == D)	// spin right
		fdf->dim.spin += 1;
	else if (keycode == A) // spin left
		fdf->dim.spin -= 1;
	else if (keycode == 120) // increse z
		fdf->dim.z_depth += 1;
	else if (keycode == 122) // decrease z
		fdf->dim.z_depth -= 1;
	give_coords(fdf->map, fdf->dim);
	printf("rot: %i, tilt: %i, spin: %i, z_depth: %i\n", fdf->dim.rotate, fdf->dim.tilt, fdf->dim.spin, fdf->dim.z_depth);
	draw_map(fdf, fdf->img);
	return (0);
}

int zoom(int button, int x, int y, t_fdf *fdf)
{	
	(void)x;
	(void)y;
	if (button == 4)
	{
		fdf->dim.rx += 1;
		fdf->dim.ry += 1;
		fdf->dim.zoom += 1;
		give_coords(fdf->map, fdf->dim);
		draw_map(fdf, fdf->img);
		// new.rz = make a preoportional thing
	}
	else if (button == 5)
	{
		fdf->dim.rx -= 1;
		fdf->dim.ry -= 1;
		fdf->dim.zoom -= 1;
		give_coords(fdf->map, fdf->dim);
		draw_map(fdf, fdf->img);
	}
	return (0);
}

void tilt(t_map *map, double degree)
{
	double res_y;
	
	map->y = make_grid_coord(map->y, 1);
	res_y = rnd((map->y * cos(THETA * degree)));
	res_y = make_grid_coord(res_y, 0);
	map->y = res_y;
}

void spin(t_map *map, double degree)
{
	double res_x;
	double res_y;
	
	map->x = map->x - (WIDTH / 2);
	map->y = make_grid_coord(map->y, 1);
	res_x = rnd((map->x * cos(THETA * degree)) + (map->y * sin(THETA * degree)));
	res_y = rnd((map->x * sin(THETA * degree)) + (map->y * cos(THETA * degree)));
	// res_x = rnd((map->x * cos(THETA * degree)));
	res_x = res_x + (WIDTH / 2);
	map->x = res_x;
	res_y = make_grid_coord(res_y, 0);
	map->y = res_y;
}