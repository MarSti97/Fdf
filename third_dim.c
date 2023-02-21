/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 22:06:56 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    tilt_3d(t_map *map, t_dim dim)
{
	int end;
	int	i;

	end = percent((dim.r_z + dim.zoom), percent(90, dim.tilt));
	i = 0;
	if (dim.tilt <= 270 && map->z > 0)
		while (i++ < (end * map->z) + (dim.z_depth * map->z))
			map->y--;
	else if (dim.tilt <= 270 && map->z < 0)
		while (i++ < (end * -map->z) + -(dim.z_depth * map->z))
			map->y++;
	end = percent((dim.r_z + dim.zoom), percent(90, 90 - (dim.tilt - 90)));
	if (dim.tilt > 90 && dim.tilt <= 270 && map->z > 0)
		while (i-- > (end * map->z) + (dim.z_depth * map->z))
			map->y++;
	else if (dim.tilt > 90 && dim.tilt <= 270 && map->z < 0)
		while (i-- > (end * -map->z) + -(dim.z_depth * map->z))
			map->y--;	
	end = percent((dim.r_z + dim.zoom), percent(90, (360 - dim.tilt)));
	if (dim.tilt > 270 && map->z > 0)
		while (i++ < (end * map->z) + (dim.z_depth * map->z))
			map->y++;
	else if (dim.tilt > 270 && map->z < 0)
		while (i++ < (end * -map->z) + -(dim.z_depth * map->z))
			map->y--;
}

// void    spin_3d(t_map *map, t_dim dim)
// {
// 	int end;
// 	int	i;

// 	end = percentage((dim.r_z + dim.zoom), percentage(90, dim.spin));
// 	i = 0;
// 	if (dim.spin <= 270 && map->z > 0)
// 		while (i++ < (end * map->z) + (map->z))
// 			map->x++;
// 	else if (dim.spin <= 270 && map->z < 0)
// 		while (i++ < (end * -map->z) + -(map->z))
// 			map->x--;
// 	end = percentage((dim.r_z + dim.zoom), percentage(90, 90 - (dim.spin - 90)));
// 	if (dim.spin > 90 && dim.spin <= 270 && map->z > 0)
// 		while (i-- > (end * map->z) + (map->z))
// 			map->x--;
// 	else if (dim.spin > 90 && dim.spin <= 270 && map->z < 0)
// 		while (i-- > (end * -map->z) + -(map->z))
// 			map->x++;	
// 	end = percentage((dim.r_z + dim.zoom), percentage(90, (360 - dim.spin)));
// 	if (dim.spin > 270 && map->z > 0)
// 		while (i++ < (end * map->z) + (map->z))
// 			map->x--;
// 	else if (dim.spin > 270 && map->z < 0)
// 		while (i++ < (end * -map->z) + -(map->z))
// 			map->x++;
// }
