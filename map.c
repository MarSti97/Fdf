/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:33:39 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/09 13:16:34 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	test_grid(t_map *map);

void    make_map(t_map **map, int fd)
{
    char *line;
    char **data;
	t_dim	dim;
	
    while (fd)
    {
        line = get_next_line(fd);
		if (!line)
			break ;
        data = ft_split(line, ' ');
        add_data(map, data);
		free (line);
    }
	dim = get_dimensions(map);
	linked_grid(*map);
	give_coords(*map, dim);
	// test_grid(*map);
}

void	test_grid(t_map *map)
{
	// t_map *temp = map;
	while (map)
	{
		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->row, map->col, map->x, map->y);
		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->next->row, map->next->col, map->next->x, map->next->y);
		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->next->next->row, map->next->next->col, map->next->next->x, map->next->next->y);
		ft_printf("\n----\n");
		map = map->down;
	}
	// ft_printf("\n");
	// while (temp)
	// {
	// 	ft_printf("Node %i: z:%i row:%i, col:%i  ->  ", i++, temp->down->z, temp->down->row, temp->down->col);
	// 	temp = temp->next;
	// }
}

void	linked_grid(t_map *map)
{
	t_map *new_line;
	t_map *temp;
	
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

void    add_data(t_map **map, char **data)
{
    t_map *node;
    static int row;
    int col;
    int i;
	// char *d;

    row++;
	i = 0;
	col = 1;
    while (data[i])
    {
		// d = data[i];
		// ft_printf("%s", d);
        node = (t_map *)malloc(sizeof(t_map));
		if (!node)
			error(*map);
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
	t_map *temp;
	int x;
	int y;
	// int	cntrx = dim.cntrx;
	// int rx = dim.rx;
	// int cmax = dim.cmax;

	// ft_printf("%i%i%i", cntrx, rx, cmax);

	y = 0;
	while (map)
	{
		x = 0;
		temp = map->down;
		while(map)
		{
			map->x = dim.cntrx - (dim.rx * (dim.cmax / 2)) + (dim.rx * x++);
			map->y = dim.cntry - (dim.ry * (dim.rmax / 2)) + (dim.ry * y);
			rotate_coord(map, 35);
			add_dimention(map, dim.rz);
			map = map->next;
		}
		map = temp;
		y++;
	}
}

t_dim   get_dimensions(t_map **map)
{
    t_map *last;
	t_dim dim;

    last = ft_listlast(*map);
	dim.cmax = last->col;
	dim.rmax = last->row;
    dim.rx = 35;
    dim.ry = 30;
	dim.rz = 3;
	dim.cntrx = WIDTH / 2;
	dim.cntry = HEIGHT / 2;
	return (dim);
}