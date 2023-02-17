/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:20 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/17 17:50:54 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		fdf->dim.z_depth += 3;
	else if (keycode == 122) // decrease z
		fdf->dim.z_depth -= 3;
	else if (keycode == P || keycode == C)
		fdf->dim = para_cent(keycode, fdf->dim);
	else
		fdf->dim = translate(keycode, fdf->dim);
	give_coords(fdf->map, fdf->dim);
	printf("rot: %i, tilt: %i, spin: %i, z_depth: %i\n", fdf->dim.rotate, fdf->dim.tilt, fdf->dim.spin, fdf->dim.z_depth);
	draw_map(fdf, fdf->img);
	return (0);
}

t_dim	para_cent(int keycode, t_dim dim)
{
	if (keycode == P)
	{
		dim.spin = 0;
		dim.tilt = 0;
		dim.rotate = 0;
	}
	else if (keycode == C)
	{
		dim.cntrx = WIDTH / 2;
		dim.cntry = HEIGHT / 2;
	}
	return (dim);
}

t_dim	translate(int keycode, t_dim dim)
{
	if (keycode == UP)
		dim.cntry -= 3;
	else if (keycode == DOWN)
		dim.cntry += 3;
	else if (keycode == LEFT)
		dim.cntrx -= 3;
	else if (keycode == RIGHT)
		dim.cntrx += 3;
	return (dim);
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
		// new.rz = make a preoportional thing
	}
	else if (button == 5 && fdf->dim.rx > 1)
	{
		fdf->dim.rx -= 1;
		fdf->dim.ry -= 1;
		fdf->dim.zoom -= 1;
	}
	give_coords(fdf->map, fdf->dim);
	draw_map(fdf, fdf->img);
	return (0);
}

