/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:20:52 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 22:24:41 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int close_x()
{
	exit (0);
	return (0);
}

t_dim	do_tilt(int keycode, t_dim dim)
{
	if (keycode == W) 	// tilt up
	{
		if (dim.tilt == 360)
			dim.tilt = 0;
		dim.tilt += 1;
	}
	else if (keycode == S) // tilt down
	{
		if (dim.tilt == 0)
			dim.tilt = 360;
		dim.tilt -= 1;
	}
	return (dim);
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
		fdf->dim.r_xy += 1;
		fdf->dim.zoom += 1;
	}
	else if (button == 5 && fdf->dim.r_xy > 1)
	{
		fdf->dim.r_xy -= 1;
		fdf->dim.zoom -= 1;
	}
	give_coords(fdf->map, fdf->dim);
	draw_map(fdf, fdf->img);
	return (0);
}
