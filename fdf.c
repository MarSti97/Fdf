/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/13 17:57:42 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_img *img, int x, int y, int colour)
{
	char	*dst;
	
	if (x > WIDTH || x < 0 || y < 0 || y > HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = colour;
}

void	draw_line(t_img *img, t_map *start, t_map *end)
{
	struct line	line;
	int e;
	int err;
	int radius;
	int i;

	line.x = start->x;
	line.y = start->y;
	line.dx = abs(end->x - line.x);
	line.dy = abs(end->y - line.y);
	line.endx = (line.x < end->x ? 1 : -1);
	line.endy = (line.y < end->y ? 1 : -1);
	
	err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	radius = get_radius(start, end);
	// printf("Node %i,%i -> radius : %i\n", start->col, start->row, radius);
	i = 0;
	while (1) //x != end->x && y != end->y
	{
		pixel_put(img, line.x, line.y, add_colour(start, end, radius, i++));
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

	temp = map->down;
	while (map->next || map->down)
	{
		if (map->next)
			draw_line(img, map, map->next);
		if (map->down)
			draw_line(img, map, map->down);
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
		win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fdf");
		img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
		
		fd = open(av[1], O_RDONLY);
		make_map(&map, fd);
		draw_map(map, &img);
		mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		controls(win, &mlx);
		mlx_loop(mlx);
	}
	else
		return(0);
}

// test_rotating(&img);
// make predefined margins later