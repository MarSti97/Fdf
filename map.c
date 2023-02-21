/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:33:39 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 21:11:53 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dim	make_map(t_map **map, int fd)
{
	char	*line;
	char	**data;
	t_dim	dim;

	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data = ft_split(line, ' ');
		add_data(map, data);
		free (line);
		free (data);
	}
	dim = get_dimensions(map);
	linked_grid(*map);
	give_coords(*map, dim);
	return (dim);
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

void	add_data(t_map **map, char **data)
{
	t_map		*node;
	static int	row;
	int			col;
	int			i;

	row++;
	i = 0;
	col = 1;
	while (data[i])
	{
		node = (t_map *)malloc(sizeof(t_map));
		if (!node)
			free_list(*map);
		node->row = row;
		node->col = col++;
		node->z = ft_atoi(data[i++]);
		node->next = NULL;
		node->down = NULL;
		ft_listadd_back(map, node);
	}
}

void	give_coords(t_map *map, t_dim dim)
{
	t_map	*map_sub;
	t_map	*temp;
	int		x;
	int		y;

	y = 0;
	map_sub = map;
	while (map_sub)
	{
		x = 0;
		temp = map_sub->down;
		while (map_sub)
		{
			map_sub->x = dim.cntrx - (dim.r_xy * (dim.cmax / 2)) + (dim.r_xy * x++);
			map_sub->y = dim.cntry - (dim.r_xy * (dim.rmax / 2)) + (dim.r_xy * y);
			rotate_coord(map_sub, dim.rotate, dim);
			tilt(map_sub, dim.tilt, dim);
			// spin(map_sub, dim.spin, dim);
			map_sub = map_sub->next;
		}
		map_sub = temp;
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
	dim.r_xy = WIDTH / (dim.cmax + dim.z_max);
	dim.r_z = dim.r_xy;
	dim.zoom = 0;
	dim.z_depth = 0;
	dim.rotate = -32;
	dim.tilt = 58;
	dim.spin = 0;
	return (dim);
}
