/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 22:18:47 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_img *img, t_map *start, t_map *end, t_dim dim)
{
	struct s_line	line;
	t_colour		colour_s;
	t_colour		colour_e;
	int 			i;

	i = 0;
	line = draw_line_two(start, end);
	dim.colour_r = my_ternery(line.dx, line.dy, line.dx, line.dy);
	colour_s = start_colour(dim, start->z);
	colour_e = end_colour(dim, end->z);
	while (line.x != end->x || line.y != end->y)
	{
		pixel_put(img, line.x, line.y, add_colour(colour_s, colour_e, dim, i++));
		line.e = line.err;
		if (line.e > -line.dx)
		{
			line.err -= line.dy;
			line.x += line.endx;
		}
		if (line.e < line.dy)
		{
			line.err += line.dx;
			line.y += line.endy;
		}
	}
}

struct s_line	draw_line_two(t_map *start, t_map *end)
{
	struct s_line	line;
	
	line.x = start->x;
	line.y = start->y;
	line.dx = abs(end->x - line.x);
	line.dy = abs(end->y - line.y);
	line.endx = my_ternery(end->x, line.x, 1, -1);
	line.endy = my_ternery(end->y, line.y, 1, -1);
	line.err = (my_ternery(line.dx, line.dy, line.dx, -line.dy) / 2);
	return (line);
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
			draw_line(img, map_sub, map_sub->next, fdf->dim);
		if (map_sub->down)
			draw_line(img, map_sub, map_sub->down, fdf->dim);
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
		fdf->img = &img;
		fd = open(av[1], O_RDONLY);
		if (fd <= 0)
			error("Error: Opening file\n", fdf, 1);
		fdf->dim = make_map(&fdf->map, fd);
		draw_map(fdf, &img);
		controls(fdf);
		mlx_loop(fdf->mlx);
	}
	else
		return(0);
	error(NULL, fdf, 0);
}
