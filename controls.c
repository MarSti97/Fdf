/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:11:20 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/13 17:58:13 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int close(int keycode)
{
	if (keycode == ESC)
		exit (0);
	return (0);
}

int close_x()
{
	exit (0);
	return (0);
}

void controls(void *win, void *mlx)
{
		mlx_hook(win, 2, 1L<<0, close, &mlx);
		mlx_hook(win, 17, 1L<<2, close_x, &mlx);
		mlx_mouse_hook(win, zoom, &mlx);
}

int zoom(int keycode)
{
	t_dim new;
	static int i;
	
	new.rx = RX;
	new.ry = RY;
	new.rz = RZ;
	if (keycode == 4)
	{
		new.rx = i++;
		new.ry = i++;
		// new.rz = make a preoportional thing
	}
	if (keycode == 5)
	{
		new.rx = i--;
		new.ry = i--;
	}
	return (0);
}