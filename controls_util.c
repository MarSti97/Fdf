/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:20:52 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 21:45:16 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dim	do_tilt(int keycode, t_dim dim)
{
	if (keycode == W)
	{
		if (dim.tilt == 360)
			dim.tilt = 0;
		dim.tilt += 1;
	}
	else if (keycode == S)
	{
		if (dim.tilt == 0)
			dim.tilt = 360;
		dim.tilt -= 1;
	}
	return (dim);
}

t_dim	do_spin(int keycode, t_dim dim)
{
	if (keycode == D)
	{
		if (dim.spin == 360)
			dim.spin = 0;
		dim.spin += 1;
	}
	else if (keycode == A)
	{
		if (dim.spin == 0)
			dim.spin = 360;
		dim.spin -= 1;
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
		dim.d = 0;
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

int	zoom(int button, int x, int y, t_fdf *fdf)
{	
	(void)x;
	(void)y;
	if (button == 4)
	{
		fdf->dim.r_xy += 1;
		fdf->dim.r_z = prcnt(fdf->dim.r_xy, 25);
;
	}
	else if (button == 5 && fdf->dim.r_xy > 1)
	{
		fdf->dim.r_xy -= 1;
		fdf->dim.r_z = prcnt(fdf->dim.r_xy, 25);

	}
	give_coords(fdf->map, fdf->dim);
	draw_map(fdf);
	return (0);
}
