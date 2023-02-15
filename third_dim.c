/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/15 20:47:09 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    add_dimention(t_map *map, t_dim dim)
{
	int end;
	int	i;
	// needs to fix
	// need to see the max high and min depth to find a ratio z
	end = (dim.tilt / dim.rz);
	i = 0;
    if (map->z > 0)
		while (i++ < end * map->z)
            map->y--;
    else if (map->z < 0)
		while (i++ < end * -map->z)
            map->y++;
	if (dim.tilt > 90)
		map->y += dim.tilt - 90;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
// write a colour ratio thing depending on the differnece in map-z
int add_colour(t_map *start, t_map *end, int radius, int i)
{
	int dif;
	int r;
	int g;
	int b;
    
	r = 153 + (8 * start->z);
	g = 00 + (8 * start->z);
	b = 255 - (8 * start->z); 
    if (start->z < end->z)
	{
		dif = (end->z * 8) / radius;
		return (create_trgb(00, r + (dif * i), g + (dif * i), b - (dif * i)));
	}
	if (start->z > end->z)
	{
		dif = rnd((((double)start->z * 8) / (double)radius) * (double)i);
		return (create_trgb(00, r - dif, g - dif, b + dif ));
	}
	if (start->z == end->z)
		return (create_trgb(00, r, g, b));
	return (create_trgb(00, 153, 100, 255));
} // grb = 00,153,00,255

// void	colour_iter(t_map *start, t_map *end, int radius, int i)
// {
// 	int dif;
// 	int colour_dif;
// 	int colour;
// 	int r;
// 	int g;
// 	int b;
    
// 	r = 153;
// 	g = 0;
// 	b = 255;
// 	colour_dif = 40;
// 	colour = colour_loop(0x009900FF, colour_dif * start->z);
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
// }

// int colour_loop(int start, int i)
// {
// 	int	r = start << 16;
// 	int	g = start << 8;
// 	int	b = start;
// 	while (i)
// 	{
// 		while (g < 255)
// 			g++;
// 		while (r > 0)
// 			r--;
// 		while (b < 255)
// 			b++;	
// 	}
// }

// int main()
// {
//     int g = 0;
//     int b = 255;
    
//     printf("address = %x\n", create_trgb(00, 153, 00, 255));
//     printf("green = %x\n", get_g(g));
//     printf("blue = %x\n", get_b(b));
// }

// int	ft_puthex(unsigned int nb, char *base)
// {
// 	int	len;

// 	len = 0;
// 	if (nb > 15)
// 		len += ft_puthex(nb / 16, base);
// 	len += write(1, &base[nb % 16], 1);
// 	return (len);
// }

// int hex_to_dec(unsigned int nb, char *base)
// {
// 	int	len;

// 	len = 0;
// 	if (nb > 15)
// 		len += ft_puthex(nb / 10, base);
// 	len += write(1, &base[nb % 10], 1);
// 	return (len);
// }

// int main()
// {
// 	unsigned int colour = 0x009900FF;

// 	colour = colour >> 2;
// 	ft_puthex(colour, "0123456789ABCDEFG");
// }