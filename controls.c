/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:20 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 22:22:59 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void controls(t_fdf *fdf)
{
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
	else if (keycode == W || keycode == S) 	// tilt up
		fdf->dim = do_tilt(keycode, fdf->dim);
	else if (keycode == 120) // increse z
		fdf->dim.z_depth += 1;
	else if (keycode == 122) // decrease z
		fdf->dim.z_depth -= 1;
	else if (keycode == P || keycode == C)
		fdf->dim = para_cent(keycode, fdf->dim);
	else
		fdf->dim = translate(keycode, fdf->dim);
	give_coords(fdf->map, fdf->dim);
	printf("rot: %i, tilt: %i, spin: %i, z_depth: %i\n", fdf->dim.rotate, fdf->dim.tilt, fdf->dim.spin, fdf->dim.z_depth);
	draw_map(fdf, fdf->img);
	return (0);
}

	// else if (keycode == D)	// spin right
	// {
	// 	if (fdf->dim.spin == 360)
	// 		fdf->dim.spin = 0;
	// 	fdf->dim.spin += 1;
	// }
	// else if (keycode == A) // spin left
	// {
	// 	if (fdf->dim.spin == 0)
	// 		fdf->dim.spin = 360;
	// 	fdf->dim.spin -= 1;
	// }
