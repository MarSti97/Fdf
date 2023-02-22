/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:20 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 17:31:44 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	controls(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, keys, fdf);
	mlx_hook(fdf->win, 17, 1L << 2, close_x, fdf);
	mlx_mouse_hook(fdf->win, zoom, fdf);
}

int	close_x(t_fdf *fdf)
{
	error(NULL, fdf, 0);
	return (0);
}

int	keys(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
		error(NULL, fdf, 0);
	if (keycode == E)
		fdf->dim.rotate -= 1;
	else if (keycode == Q)
		fdf->dim.rotate += 1;
	else if (keycode == W || keycode == S)
		fdf->dim = do_tilt(keycode, fdf->dim);
	else if (keycode == D || keycode == A)
		fdf->dim = do_spin(keycode, fdf->dim);
	else if (keycode == 120)
		fdf->dim.d += 1;
	else if (keycode == 122)
		fdf->dim.d -= 1;
	else if (keycode == P || keycode == C)
		fdf->dim = para_cent(keycode, fdf->dim);
	else
		fdf->dim = translate(keycode, fdf->dim);
	give_coords(fdf->map, fdf->dim);
	draw_map(fdf);
	return (0);
}
