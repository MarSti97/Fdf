/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/08 21:27:34 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

// int close()
// {
// 	exit (0);
// 	return (0);
// }

void	pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;
	
	if (x > WIDTH || x < 0 || y < 0 || y > HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = colour;
}

// void	reverse_line(t_img *img, t_map *start, t_map *end, int dx)
// {
// 	struct line	line;

// 	line.dy = start->y - end->y;
// 	line.x = (end->x > start->x ? start->x : end->x);
// 	line.y = (end->x > start->x ? start->y : end->y);
// 	line.d = 2 * (line.dy - dx);
// 	line.finishx = (end->x > start->x ?  end->x : start->x);
// 	line.finishy = (end->x > start->x ?  end->y : start->y);
// 	while(line.x < line.finishx)
// 	{
// 		if (line.d >= 0)
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.y--;
// 			line.d = line.d + 2 * line.dy - 2 * dx;
// 		}
// 		else
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.d = line.d + 2 * line.dy;	
// 		}
// 		line.x++;
// 	}
// 	while (line.y != line.finishy)
// 		pixel_put(img, line.x, line.y--, 0x009900FF);
// }

// void	bresenham_line(t_img *img, t_map *start, t_map *end)
// {
// 	struct line	line;

// 	line.dx = (end->x > start->x ? (end->x - start->x) : (start->x - end->x));
// 	if (end->y < start->y)
// 		return (reverse_line(img, start, end, line.dx));
// 	line.dy = end->y - start->y;
// 	line.x = (end->x > start->x ? start->x : end->x);
// 	line.y = (end->x > start->x ? start->y : end->y);
// 	// line.y = start->y;
// 	line.d = 2 * (line.dy - line.dx);
// 	line.finishx = (end->x > start->x ?  end->x : start->x);
// 	line.finishy = (end->x > start->x ?  end->y : start->y);
// 	while(line.x < line.finishx)
// 	{
// 		if (line.d >= 0)
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.y++;
// 			line.d = line.d + 2 * line.dy - 2 * line.dx;
// 		}
// 		else
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.d = line.d + 2 * line.dy;	
// 		}
// 		line.x++;
// 	}
// 	while (line.y < line.finishy)
// 		pixel_put(img, line.x, line.y++, 0x009900FF);
// 	while (line.y > line.finishy)
// 		pixel_put(img, line.x, line.y--, 0x009900FF);
// }

void	draw_line(t_img *img, t_map *start, t_map *end)
{
	struct line	line;
	int e;
	int err;

	line.x = start->x;
	line.y = start->y;
	line.dx = abs(end->x - line.x);
	line.dy = abs(end->y - line.y);
	line.endx = (line.x < end->x ? 1 : -1);
	line.endy = (line.y < end->y ? 1 : -1);
	
	err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (1) //x != end->x && y != end->y
	{
		pixel_put(img, line.x, line.y, 0x009900FF);
		if (line.x == end->x && line.y == end->y)
			break;
		e = err;
		if (e > -line.dx)
		{
			err -= line.dy;
			line.x += line.endx;
		}
		if (e < line.dy)
		{
			err += line.dx;
			line.y += line.endy;
		}
	}
}

void	draw_map(t_map *map, t_img *img)
{
	t_map *temp;
	// struct coordinates	coord;

	temp = map->down;
	while (map->next || map->down)
	{
		if (map->next)
			// bresenham_line(img, map, map->next);
			draw_line(img, map, map->next);
		if (map->down)
		{
			// bresenham_line(img, map, map->down);
			draw_line(img, map, map->down);
		}
		if (map->next)
			map = map->next;
		else if (map->down)
		{
			map = temp;
			temp = temp->down;
		}
	}
}

int	main(int ac, char **av)
{
	int fd;
	void *mlx;
	void *win;
	t_img	img;
	t_map   *map;
    
    map = NULL;
	if (ac == 2)
	{
		mlx = mlx_init();
		win = mlx_new_window(mlx, WIDTH, HEIGHT, "Lets make shit");
		img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
		
		fd = open(av[1], O_RDONLY);
		make_map(&map, fd);
		// draw_circle(&img);
		draw_map(map, &img);
		// test_rotating(&img);
		mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		mlx_hook(win, 17, 1L<<2, close, &mlx);
		mlx_loop(mlx);
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