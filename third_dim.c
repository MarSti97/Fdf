/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 17:32:51 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	tilt_3d(t_map *map, t_dim dim)
{
	int	end;
	int	i;

	end = prcnt((dim.r_z + dim.d) * map->z, prcnt(90, dim.tilt));
	i = 0;
	if (dim.tilt <= 270 && map->z > 0)
		while (i++ < end)
			map->y--;
	else if (dim.tilt <= 270 && map->z < 0)
		while (i++ < -end)
			map->y++;
	end = prcnt((dim.r_z + dim.d) * map->z, prcnt(90, 90 - (dim.tilt - 90)));
	if (dim.tilt > 90 && dim.tilt <= 270 && map->z > 0)
		while (i-- > end)
			map->y++;
	else if (dim.tilt > 90 && dim.tilt <= 270 && map->z < 0)
		while (i-- > -end)
			map->y--;
	end = prcnt((dim.r_z + dim.d) * map->z, prcnt(90, (360 - dim.tilt)));
	if (dim.tilt > 270 && map->z > 0)
		while (i++ < end)
			map->y++;
	else if (dim.tilt > 270 && map->z < 0)
		while (i++ < -end)
			map->y--;
}

void	spin_3d(t_map *map, t_dim dim)
{
	int	end;
	int	i;

	end = prcnt((dim.r_z + dim.d) * map->z, prcnt(90, dim.spin));
	i = 0;
	if (dim.spin <= 270 && map->z > 0)
		while (i++ < end)
			map->x++;
	else if (dim.spin <= 270 && map->z < 0)
		while (i++ < -end)
			map->x--;
	end = prcnt((dim.r_z + dim.d) * map->z, prcnt(90, 90 - (dim.spin - 90)));
	if (dim.spin > 90 && dim.spin <= 270 && map->z > 0)
		while (i-- > end)
			map->x--;
	else if (dim.spin > 90 && dim.spin <= 270 && map->z < 0)
		while (i-- > -end)
			map->x++;
	end = prcnt((dim.r_z + dim.d) * map->z, prcnt(90, (360 - dim.spin)));
	if (dim.spin > 270 && map->z > 0)
		while (i++ < end)
			map->x--;
	else if (dim.spin > 270 && map->z < 0)
		while (i++ < -end)
			map->x++;
}
