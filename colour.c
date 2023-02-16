/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:56:40 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/16 18:30:44 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	colour_iter(t_map *start, t_map *end, int radius, int i)
{
	int dif;
	int ratio_colour;
    
	ratio_colour = 20;
    if (start->z < end->z)
	{
		dif = get_dif(start->z, end->z, radius, ratio_colour);
		return (colour_loop(510 + (start->z * ratio_colour) + (dif * i)));
	}
	if (start->z > end->z)
	{
		dif = get_dif(start->z, end->z, radius, ratio_colour);
		// dif = rnd((((double)start->z * 8) / (double)radius) * (double)i);
		return (colour_loop(510 + (start->z * ratio_colour) - (dif * i)));
	}
	return (colour_loop(510 + (start->z * ratio_colour)));
    // return (create_trgb(00, 255, 00, 255));
}

int	get_dif(int start, int end, int radius, int ratio)
{
	int beg;
	int fin;
	int res;

	res = 0;
	beg = my_ternery(start, end, end, start);
	fin = my_ternery(start, end, start, end);
	while (beg++ < fin)
		res++;
    res = (res * ratio) / radius;
	return (res);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int colour_loop(int i)
{
	int	r = 0;
	int	g = 255;
	int	b = 255;
	while (i > 0)
	{
		while (g-- > 0 && i > 0)
			i--;
		while (r++ < 254 && i > 0)
			i--;
		while (b-- > 0 && i > 0)
			i--;
		while (g++ < 254 && i > 0)
			i--;
		while (b++ < 254 && i > 0)
			i--;
        break;
	}
    // printf("r: %i\n", r);
    // printf("g: %i\n", g);
    // printf("b: %i\n", b);
	return (create_trgb(00, r, g, b));
}
// lowest colour (0, 255, 255)
// highest colour (255, 255, 0)
// 4 loops low to high
// base colour (255, 0, 255)
// int main()
// {
//     int dif = get_dif(0, 10, 22);
//     printf("dif: %i\n", dif);
// }
