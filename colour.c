/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:56:40 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 11:45:12 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_colour	get_colour_dif(t_dim dim, t_colour zero, int z)
{
	t_colour	top;
	t_colour	bottom;
	t_colour	res;
	int			divider;

	top = get_rgb(COLOUR_TOP);
	bottom = get_rgb(COLOUR_BOTTOM);
	divider = my_ternery(0, z, dim.z_min, dim.z_max);
	if (z == 0)
		return (zero);
	res.r = ((my_ternery(0, z, bottom.r, top.r) - zero.r) / divider);
	res.g = ((my_ternery(0, z, bottom.g, top.g) - zero.g) / divider);
	res.b = ((my_ternery(0, z, bottom.b, top.b) - zero.b) / divider);
	return (res);
}

int	split_colour(t_colour start, t_colour end, t_dim dim, int i)
{
	t_colour	res;
	t_colour	base;
	double		div;
	static int	half;

	base = get_rgb(COLOUR_ZERO);
	div = ((double)abs(start.s_z) / (abs(start.s_z) + abs(end.e_z)));
	if (i < (dim.rad * div))
	{
		res.r = (start.r + calc((base.r - start.r), (dim.rad * div), i));
		res.g = (start.g + calc((base.g - start.g), (dim.rad * div), i));
		res.b = (start.b + calc((base.b - start.b), (dim.rad * div), i));
		half = i;
	}
	else
	{
		div = ((double)abs(end.e_z) / (abs(start.s_z) + abs(end.e_z)));
		res.r = (base.r + calc((end.r - base.r), (dim.rad * div), (i - half)));
		res.g = (base.g + calc((end.g - base.g), (dim.rad * div), (i - half)));
		res.b = (base.b + calc((end.b - base.b), (dim.rad * div), (i - half)));
	}
	return (create_trgb(0, res.r, res.g, res.b));
}

int	add_colour(t_colour start, t_colour end, t_dim dim, int i)
{
	t_colour	res;

	if ((start.s_z * end.e_z) < 0)
		return (split_colour(start, end, dim, i));
	else if (start.s_z != end.e_z)
	{
		res.r = (start.r + calc((end.r - start.r), dim.rad, i));
		res.g = (start.g + calc((end.g - start.g), dim.rad, i));
		res.b = (start.b + calc((end.b - start.b), dim.rad, i));
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
