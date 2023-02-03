/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/03 17:27:32 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

/* int	main(int ac, char **av)
{
	int fd;
	char *str;

	if (ac == 2)
	{
		check_arg(av[1]);
		fd = open(av[1], O_RDONLY);
		str = get_next_line(fd);
		// make array of ints with atoi 
	}
	else
		return(0);
} */

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

void	bresenham_line(t_img *img)
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

void	make_grid(t_img *img, int x_points, int y_points, int x_win, int y_win)
{
	int	x_len = 640 - 10;
	int	y_len = 360 - 10;
	int x = x_len / x_points;
	int	y = y_len / y_points;
	int	counter = 0;
	while (counter != (x_points + y_points))
	{
		coord.x_start = x_len;
		coord.y_start = y_len;
		coord.x_end = ;
		coord.y_end = 34;
		bresenham_line(img);	
	}
}

int	main()
{
	void *mlx;
	void *win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 360, "Lets make shit");
	img.img = mlx_new_image(mlx, 640, 360);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	
	make_grid(&img, 8, 8);
	// draw_line(&img, 100, 100);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_hook(win, 17, 1L<<2, close, &mlx);
	mlx_loop(mlx);
	// void *image = mlx_new_image(mlx, 640, 360);
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