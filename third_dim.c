/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/16 21:25:24 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    add_dimention(t_map *map, t_dim dim)
{
	int end;
	int	sub;
	int	i;
	// needs to fix
	// need to see the max high and min depth to find a ratio z
	// make a base z height, then use a percentage of of it depending on the tilt 0 - 90 max
	sub = 0;
	if (dim.tilt > 90)
		sub = dim.tilt - 90; // if i wanna do 360 need to make a function do take care of all conditions
	end = percentage((RZ + dim.zoom), percentage(90, dim.tilt - sub));
	i = 0;
    if (map->z > 0)
		while (i++ < (end * map->z) + dim.z_depth)
            map->y--;
    else if (map->z < 0)
		while (i++ < (end * -map->z) + dim.z_depth)
            map->y++;
	if (dim.tilt > 90 && map->z != 0)
		map->y += dim.tilt - 90;
}


// write a colour ratio thing depending on the differnece in map-z
// int add_colour(t_map *start, t_map *end, int radius, int i)
// {
// 	int dif;
// 	int r;
// 	int g;
// 	int b;
    
// 	r = 153 + (8 * start->z);
// 	g = 00 + (8 * start->z);
// 	b = 255 - (8 * start->z); 
//     if (start->z < end->z)
// 	{
// 		dif = (end->z * 8) / radius;
// 		return (create_trgb(00, r + (dif * i), g + (dif * i), b - (dif * i)));
// 	}
// 	if (start->z > end->z)
// 	{
// 		dif = rnd((((double)start->z * 8) / (double)radius) * (double)i);
// 		return (create_trgb(00, r - dif, g - dif, b + dif ));
// 	}
// 	if (start->z == end->z)
// 		return (create_trgb(00, r, g, b));
// 	return (create_trgb(00, 153, 100, 255));
// } // grb = 00,153,00,255