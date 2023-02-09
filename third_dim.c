/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:05:27 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/09 11:24:09 by mstiedl          ###   ########.fr       */
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

int add_colour(t_map *map, int arg)
{
	int colour;
	
	colour = 0x009900FF;
    if (map->z != 0)
	{
		colour = colour << arg;
		return (colour);
	}
	return (colour);
}

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