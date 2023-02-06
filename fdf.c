/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/06 15:18:16 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int close()
{
	exit (0);
	return (0);
}

void	pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;
	
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = colour;
}

void	bresenham_line(t_img *img, struct coordinates coord)
{
	int	d;
	int	x;
	int	y;
	int dx;
	int	dy;

	dx = coord.x_end - coord.x_start;
	dy = coord.y_end - coord.y_start;
	x = coord.x_start;
	y = coord.y_start;
	d = 2 * (dy - dx);
	while(x < coord.x_end)
	{
		if (d >= 0)
		{
			pixel_put(img, x, y, 0x00FF0000);
			y++;
			d = d + 2 * dy - 2 * dx;
		}
		else
		{
			pixel_put(img, x, y, 0x00FF0000);
			d = d + 2 * dy;	
		}
		x++;
	}	
}

void	draw_map(t_map **map, t_img *img)
{
	t_map *temp;
	struct coordinates	coord;

	temp = (*map)->down;
	while ((*map)->next && (*map)->down)
	{
		coord.x_start = (*map)->x;
		coord.y_start = (*map)->y;
		coord.x_end = (*map)->next->x;
		coord.y_end = (*map)->next->y;
		bresenham_line(img, coord);
		if ((*map)->down)
		{
			coord.x_end = (*map)->down->x;
			coord.y_end = (*map)->down->y;
			bresenham_line(img, coord);
		}
		if ((*map)->next)
			*map = (*map)->next;
		else if ((*map)->down)
		{
			*map = temp;
			temp = temp->down;
		}
	}
}

int	main(int ac, char **av)
{
	int fd;
	// void *mlx;
	// void *win;
	t_img	img;
	t_map   *map;
    
    map = NULL;
	if (ac == 2)
	{
		// mlx = mlx_init();
		// win = mlx_new_window(mlx, 1080, 640, "Lets make shit");
		// img.img = mlx_new_image(mlx, 1080, 640);
		// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
		
		fd = open(av[1], O_RDONLY);
		make_map(&map, fd);
		draw_map(&map, &img);
		// draw_line(&img, 100, 100);
		// mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		// mlx_hook(win, 17, 1L<<2, close, &mlx);
		// mlx_loop(mlx);
		// void *image = mlx_new_image(mlx, 640, 360);
	}
	else
		return(0);
}

// make predefined margins later
/* // need to plot the whole grid, and light up every pixel
void	draw_line(t_img	*img)
{	
	int x;
	int	y;

	x = coord.x_start;
	y = coord.y_start;
	while (x != coord.x_end && y != coord.y_end)
	{
		calcuate_next_pixel()		
		pixel_put(img, x++, y, 0x00FF0000);
	}
	while (y < coord.y_end)
		pixel_put(img, x, y++, 0x00FF0000);
	while (x > 5 && 7 > 5)
	{
		pixel_put(img, x--, y--, 0x00FF0000);	
		pixel_put(img, x, y--, 0x00FF0000);	
	}
	while (y > 5)
		pixel_put(img, x, y--, 0x00FF0000);	
	
} */