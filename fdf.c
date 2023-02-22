/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:21 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 12:58:03 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_img *img, t_map *start, t_map *end, t_dim dim)
{
	struct s_line	line;
	t_colour		col_s;
	t_colour		col_e;
	int				i;

	i = 0;
	line = draw_line_two(start, end);
	dim.rad = my_ternery(line.dx, line.dy, line.dx, line.dy);
	col_s = start_colour(dim, start->z);
	col_e = end_colour(dim, end->z);
	while (line.x != end->x || line.y != end->y)
	{
		pixel_put(img, line.x, line.y, add_colour(col_s, col_e, dim, i++));
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

void	draw_map(t_fdf *fdf)
{
	t_map	*temp;
	t_map	*map_sub;

	map_sub = fdf->map;
	temp = map_sub->down;
	ft_bzero(fdf->img->addr, sizeof(fdf->img->bpp) * HEIGHT * WIDTH);
	while (map_sub->next || map_sub->down)
	{
		if (map_sub->next)
			draw_line(fdf->img, map_sub, map_sub->next, fdf->dim);
		if (map_sub->down)
			draw_line(fdf->img, map_sub, map_sub->down, fdf->dim);
		if (map_sub->next)
			map_sub = map_sub->next;
		else if (map_sub->down)
		{
			map_sub = temp;
			temp = temp->down;
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_img	img;
	t_fdf	*fdf;

	if (ac == 2)
	{
		fdf = (t_fdf *)malloc(sizeof(t_fdf));
		if (!fdf)
			exit (1);
		fdf->map = NULL;
		fdf->mlx = mlx_init();
		fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "Fdf");
		img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.edn);
		fdf->img = &img;
		make_map(&fdf, av[1]);
		draw_map(fdf);
		controls(fdf);
		mlx_loop(fdf->mlx);
	}
	else
		return (0);
}
