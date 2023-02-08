/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/08 21:20:51 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    add_dimention(t_map *map)
{
    int i;

    i = 0;
    if (map->z > 0)
        while (i++ != map->z)
            map->y -= 3;
    else if (map->z < 0)
        while (i-- != map->z)
            map->y += 3;
}

// void    add_colour()
// {
    
// }