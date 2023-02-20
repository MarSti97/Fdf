/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:56:40 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/20 22:39:46 by mstiedl          ###   ########.fr       */
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

t_colour	get_colour_dif(t_dim dim, t_colour zero, int z)
{
	t_colour	top = get_rgb(COLOUR_TOP);
	t_colour	bottom = get_rgb(COLOUR_BOTTOM);
	t_colour	res;
	int			divider = my_ternery(0, z, dim.z_min, dim.z_max);
	
	if (z == 0)
		return(zero);
	res.r = ((my_ternery(0, z, bottom.r, top.r) - zero.r) / divider);
	res.g = ((my_ternery(0, z, bottom.g, top.g) - zero.g) / divider);
	res.b = ((my_ternery(0, z, bottom.b, top.b) - zero.b) / divider);
	return (res);
}

int do_accurate_op(double dif, double radius, double inc)
{
	return(rnd((dif / radius) * inc));
}

int	split_colour(t_colour start, t_colour end, t_dim dim, int i)
{
	t_colour	res;
	t_colour	base = get_rgb(COLOUR_ZERO);
	double		divide = ((double)abs(start.s_z) / (abs(start.s_z) + abs(end.e_z)));
	static int	half;

	if (i < (dim.colour_r * divide))
	{
		res.r = (start.r + do_accurate_op((base.r - start.r), (dim.colour_r * divide), i));
		res.g = (start.g + do_accurate_op((base.g - start.g), (dim.colour_r * divide), i));
		res.b = (start.b + do_accurate_op((base.b - start.b), (dim.colour_r * divide), i));
		half = i;
	}
	else
	{
		divide = ((double)abs(end.e_z) / (abs(start.s_z) + abs(end.e_z)));
		res.r = (base.r + do_accurate_op((end.r - base.r), (dim.colour_r * divide), (i - half)));
		res.g = (base.g + do_accurate_op((end.g - base.g), (dim.colour_r * divide), (i - half)));
		res.b = (base.b + do_accurate_op((end.b - base.b), (dim.colour_r * divide), (i - half)));
	}
	return (create_trgb(0, res.r, res.g, res.b));
} 

int add_colour(t_colour start, t_colour end, t_dim dim, int i)
{
	t_colour	res;
	
	if ((start.s_z * end.e_z) < 0)
		return(split_colour(start, end, dim, i));
	else if (start.s_z != end.e_z)
	{
		res.r = (start.r + do_accurate_op((end.r - start.r), dim.colour_r, i));
		res.g = (start.g + do_accurate_op((end.g - start.g), dim.colour_r, i));
		res.b = (start.b + do_accurate_op((end.b - start.b), dim.colour_r, i));
	}
	else
		return (create_trgb(0, start.r, start.g, start.b));
	return (create_trgb(0, res.r, res.g, res.b));
}

t_colour	start_colour(t_dim dim, int start_z)
{
	t_colour	dif;
	t_colour	base;
	t_colour	res;

	base = get_rgb(COLOUR_ZERO);
	dif = get_colour_dif(dim, base, start_z);
	res.r = base.r + (dif.r * start_z);
	res.g = base.g + (dif.g * start_z);
	res.b = base.b + (dif.b * start_z);
	res.s_z = start_z;
	return (res);
}

t_colour	end_colour(t_dim dim, int end_z)
{
	t_colour	dif;
	t_colour	base;
	t_colour	res;

	base = get_rgb(COLOUR_ZERO);
	dif = get_colour_dif(dim, base, end_z);
	res.r = base.r + (dif.r * end_z);
	res.g = base.g + (dif.g * end_z);
	res.b = base.b + (dif.b * end_z);
	res.e_z = end_z;
	return (res);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
