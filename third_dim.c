/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/12 22:31:00 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    add_dimention(t_map *map, int ratio)
{
    int i;

    i = 0;
    if (map->z > 0)
        while (i++ != map->z)
            map->y -= ratio;
    else if (map->z < 0)
        while (i-- != map->z)
            map->y += ratio;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int add_colour(t_map *start, t_map *end, int radius, int i)
{
	int colour;
    int ratio;
    
	ratio = radius / start->z
	colour = 0x009900FF;
    if (start->z != 0 || end->z != 0)
	{
		return (create_trgb(00, 153, 00, 255));
	}
	return (colour);
}

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