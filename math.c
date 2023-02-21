/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:25:49 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/21 22:28:58 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	pythag(int a, int b)
{
	double c;
	
	a *= a;
	b *= b;
	c = a + b;
	c = sqrt(c);
	return (c);
}

int rnd(double nbr)
{
	int whole = nbr;
	double decimal = 0.5;

	decimal = decimal + whole;
	if (nbr <= decimal)
		return (nbr);
	return (nbr + 1); 
}

int	percent(double full, double percent)
{
	return(rnd((full * percent) / 100));
}

// double	get_radius(t_map *start, t_map *end)
// {
// 	int x_len;
// 	int y_len;
// 	double radius;
	
// 	x_len = my_ternery(start->x, end->x, (start->x - end->x), (end->x - start->x));
// 	y_len = my_ternery(start->y, end->y, (start->y - end->y), (end->y - start->y));
// 	radius = pythag(x_len, y_len);
// 	return (radius);
// }