/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:25:49 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/16 20:49:49 by mstiedl          ###   ########.fr       */
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

int	percentage(double full, double percent)
{
	return(rnd((full * percent) / 100));
}