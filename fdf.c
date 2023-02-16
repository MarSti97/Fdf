/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/16 17:24:00 by mstiedl          ###   ########.fr       */
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
	struct s_line	line;
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
		pixel_put(img, line.x, line.y, colour_iter(start, end, radius, i++));
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

void	draw_map(t_fdf *fdf, t_img *img)
{
	t_map	*temp;
	t_map	*map_sub;
	
	map_sub = fdf->map;
	temp = map_sub->down;
	ft_bzero(img->addr, sizeof(img->bpp) * HEIGHT * WIDTH);
	while (map_sub->next || map_sub->down)
	{
		if (map_sub->next)
			draw_line(img, map_sub, map_sub->next);
		if (map_sub->down)
			draw_line(img, map_sub, map_sub->down);
		if (map_sub->next)
			map_sub = map_sub->next;
		else if (map_sub->down)
		{
			map_sub = temp;
			temp = temp->down;
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, img->img, 0, 0);
}

int	main(int ac, char **av)
{
	int fd;
	t_img	img;
	t_fdf	*fdf;
    
	if (ac == 2)
	{
		fdf = (t_fdf *)malloc(sizeof(t_fdf));
		if (!fdf)
			return (0);
		fdf->map = NULL;
		fdf->mlx = mlx_init();
		fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "Fdf");
		img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
		fd = open(av[1], O_RDONLY);
		fdf->dim = make_map(&fdf->map, fd);
		draw_map(fdf, &img);
		controls(fdf, &img);
		mlx_loop(fdf->mlx);
	}
	else
		return(0);
}

// test_rotating(&img);
// make predefined margins later