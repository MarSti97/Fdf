/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:56:40 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/17 19:27:15 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_colour	get_rgb(int colour)
{
	t_colour	rgb;
	
	rgb.r = colour >> 16;
	rgb.g = colour >> 8 & 0xFF;
	rgb.b = colour & 0xFF;
	return(rgb);
}

t_colour	get_colour_dif(t_dim dim)
{
	t_colour	start_colour = get_rgb(COLOUR_START);
	t_colour	highest_point_colour = get_rgb(COLOUR_END);
	t_colour	res;
	
	res.r = ((start_colour.r - highest_point_colour.r) / dim.z_max);
	res.g = ((start_colour.g - highest_point_colour.g) / dim.z_max);
	res.b = ((start_colour.b - highest_point_colour.b) / dim.z_max);
	return (res);
}

// t_colour	get_colour_dif_neg(t_dim dim)
// {
// 	t_colour	start_colour = get_rgb(0x009900FF);
// 	t_colour	lowest_point_colour = get_rgb(0x00FCFF);
// 	t_colour	res;
	
// 	res.r = ((start_colour.r - lowest_point_colour.r) / dim.z_min);
// 	res.g = ((start_colour.g - lowest_point_colour.g) / dim.z_min);
// 	res.b = ((start_colour.b - lowest_point_colour.b) / dim.z_min);
// 	return (res);
// }

int add_colour(t_colour start, t_colour i, t_dim dim, int change)
{
	// t_colour	dif_neg = get_colour_dif_neg(dim);
	t_colour	res;
	
	if (start.s_z < start.e_z)
	{
		res.r = (start.r + ((dim.colour_r / i.r) * change));
		res.g = (start.g + ((dim.colour_r / i.g) * change));
		res.b = (start.b + ((dim.colour_r / i.b) * change));
		return (create_trgb(0, res.r, res.g, res.b));	
	}
	else if (start.s_z > start.e_z)
	{
		res.r = (start.r - ((i.r / dim.colour_r)) * change);
		res.g = (start.g - ((i.g / dim.colour_r)) * change);
		res.b = (start.b - ((i.b / dim.colour_r)) * change);
		return (create_trgb(0, res.r, res.g, res.b));
	}
	return (create_trgb(0, start.r, start.g, start.b));
}

t_colour	start_colour(t_colour dif, int start_z, int end_z)
{
	t_colour	base;
	t_colour	res;

	base = get_rgb(COLOUR_START);
	res.r = base.r + (dif.r * start_z);
	res.g = base.g + (dif.g * start_z);
	res.b = base.b + (dif.b * start_z);
	res.s_z = start_z;
	res.e_z = end_z;
	return (res);
}

// int	colour_iter(t_map *start, t_map *end, int radius, int i)
// {
// 	int	dif;
// 	int	ratio_colour;

// 	ratio_colour = 20;
// 	if (start->z < end->z)
// 	{
// 		dif = get_dif(start->z, end->z, radius, ratio_colour);
// 		return (colour_loop(510 + (start->z * ratio_colour) + (dif * i)));
// 	}
// 	if (start->z > end->z)
// 	{
// 		dif = get_dif(start->z, end->z, radius, ratio_colour);
// 		// dif = rnd((((double)start->z * 8) / (double)radius) * (double)i);
// 		return (colour_loop(510 + (start->z * ratio_colour) - (dif * i)));
// 	}
// 	return (colour_loop(510 + (start->z * ratio_colour)));
//     // return (create_trgb(00, 255, 00, 255));
// }

// int	get_dif(int start, int end, int radius, int ratio)
// {
// 	int	beg;
// 	int	fin;
// 	int	res;

// 	res = 0;
// 	beg = my_ternery(start, end, end, start);
// 	fin = my_ternery(start, end, start, end);
// 	while (beg++ < fin)
// 		res++;
// 	res = (res * ratio) / radius;
// 	return (res);
// }

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// int	colour_loop(int i)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = 0;
// 	g = 255;
// 	b = 255;
// 	while (i > 0)
// 	{
// 		while (g-- > 0 && i > 0)
// 			i--;
// 		while (r++ < 254 && i > 0)
// 			i--;
// 		while (b-- > 0 && i > 0)
// 			i--;
// 		while (g++ < 254 && i > 0)
// 			i--;
// 		while (b++ < 254 && i > 0)
// 			i--;
// 		break;
// 	}
// 	return (create_trgb(00, r, g, b));
// }
// lowest colour (0, 255, 255)
// highest colour (255, 255, 0)
// 4 loops low to high
// base colour (255, 0, 255)
