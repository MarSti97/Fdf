/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:33:39 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 22:23:21 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_map(t_fdf **fdf, char *file)
{
	char	*line;
	char	**data;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		error("Error: Opening file\n", fdf, 1);
	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data = ft_split(line, ' ');
		if (!data)
			error("Error: Reading file\n", fdf, 1);
		add_data(fdf, data);
		free_data(data);
		free (line);
	}
	(*fdf)->dim = get_dimensions(&(*fdf)->map);
	linked_grid((*fdf)->map);
	give_coords((*fdf)->map, (*fdf)->dim);
}

void	linked_grid(t_map *map)
{
	t_map	*new_line;
	t_map	*temp;

	new_line = map;
	while (new_line->row == new_line->next->row)
		new_line = new_line->next;
	new_line = new_line->next;
	while (new_line)
	{
		map->down = new_line;
		temp = map;
		map = map->next;
		new_line = new_line->next;
		if (temp->row != temp->next->row)
			temp->next = NULL;
	}
}

void	add_data(t_fdf **fdf, char **data)
{
	t_map		*node;
	static int	row;
	int			col;
	int			i;

	row++;
	i = 0;
	col = 1;
	if (!data)
		return ;
	while (data[i])
	{
		node = (t_map *)malloc(sizeof(t_map));
		if (!node)
			free_list((*fdf)->map);
		node->row = row;
		node->col = col++;
		node->z = ft_atoi(data[i++]);
		node->next = NULL;
		node->down = NULL;
		ft_listadd_back(&(*fdf)->map, node);
	}
}

void	give_coords(t_map *map, t_dim dim)
{
	t_map	*sub;
	t_map	*temp;
	int		x;
	int		y;

	y = 0;
	sub = map;
	while (sub)
	{
		x = 0;
		temp = sub->down;
		while (sub)
		{
			sub->x = dim.cntrx - (dim.r_xy * (dim.cmax / 2)) + (dim.r_xy * x++);
			sub->y = dim.cntry - (dim.r_xy * (dim.rmax / 2)) + (dim.r_xy * y);
			rotate_coord(sub, dim.rotate, dim);
			tilt(sub, dim.tilt, dim);
			spin(sub, dim.spin, dim);
			sub = sub->next;
		}
		sub = temp;
		y++;
	}
}

t_dim	get_dimensions(t_map **map)
{
	t_map	*last;
	t_dim	dim;

	last = ft_listlast(*map);
	dim.cmax = last->col;
	dim.rmax = last->row;
	dim.cntrx = WIDTH / 2;
	dim.cntry = HEIGHT / 2;
	dim.z_max = get_z_max(*map);
	dim.z_min = get_z_min(*map);
	dim.r_xy = ((WIDTH + HEIGHT) / 2) / (dim.cmax);
	dim.r_z = prcnt(dim.r_xy, 25);
	dim.d = 0;
	dim.rotate = -32;
	dim.tilt = 58;
	dim.spin = 0;
	return (dim);
}
