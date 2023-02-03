/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:25:49 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/03 15:27:29 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

int	pythag(int a, int b)
{
	double c;
	
	a *= a;
	b *= b;
	c = a + b;
	c = sqrt(c);
	return (c);
}

int main()
{
	int diag;

	diag = pythag(15, 15);
}