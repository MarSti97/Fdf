/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:33:39 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/05 19:25:41 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    make_map(int fd)
{
    char *line;
    char **data;
    t_map   *map;
    
    map = NULL;
    while (line)
    {
        line = get_next_line(fd);
        data = ft_split(line, ' ');
        add_data(&map, data);
    }
    link_rows(&map);
}

void    add_data(t_map **map, char **data)
{
    t_map *node;
    static int row;
    int col;
    int i;

    row++;
    while (data[i++])
    {
        node = (*t_map)malloc(sizeof(t_map));
        node->row = row;
        node->col = ++col;
        node->z = ft_atoi(data[i]);
        node->next = NULL;
        node->down = NULL;
        // if (col == 1 && row != 1)
        //     link_rows();
        ft_lstaddlast(map, node); // check the function
    }
}

void    map_dimentions(t_map **map)
{
    t_map *last;
    int ratio_x;
    int ratio_y;

    last = ft_lstlast(map);
    ratio_x = 1080 / map->row;
    ratio_y = 640 / map->col;
}