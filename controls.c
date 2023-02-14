/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:20 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/14 18:18:51 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int keys(int keycode, void *param);

int close_x()
{
	exit (0);
	return (0);
}

void controls(t_fdf *fdf, t_img *img)
{
	fdf->img = img;
	mlx_key_hook(fdf->win, keys, fdf->mlx);
	// mlx_hook(fdf->win, 2, 1L<<0, keys, fdf->mlx);
	mlx_hook(fdf->win, 17, 1L<<2, close_x, fdf->mlx);
	// mlx_hook(fdf->win, 4, 0, zoom, fdf);
	mlx_mouse_hook(fdf->win, zoom, fdf);
}

int keys(int keycode, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (keycode == ESC)
		exit (0);
	if (keycode == E) // rotate right
	{
		fdf->dim.rotate -= 1;
		give_coords(fdf->map, fdf->dim);
		draw_map(fdf, fdf->img);
	}
	else if (keycode == Q) // rotate left
	{
		fdf->dim.rotate -= 1;
		give_coords(fdf->map, fdf->dim);
		draw_map(fdf, fdf->img);
	}
	// else if (keycode == W)
	// 	// tilt up
	// else if (keycode == S)
	// 	// tilt down
	// else if (keycode == D)
	// 	// spin right
	// else if (keycode == A)
		// spin left
	return (0);
}

int zoom(int button, int x, int y, void *param)
{
	t_fdf *fdf;
	
	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (button == 4)
	{
		fdf->dim.rx += 1;
		fdf->dim.ry += 1;
		give_coords(fdf->map, fdf->dim);
		draw_map(fdf, fdf->img);
		// new.rz = make a preoportional thing
	}
	else if (button == 5)
	{
		fdf->dim.rx -= 1;
		fdf->dim.ry -= 1;
		give_coords(fdf->map, fdf->dim);
		draw_map(fdf, fdf->img);
	}
	return (0);
}